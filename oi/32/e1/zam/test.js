import { $ } from "bun";
import * as fs from "fs";
const files = (await $`ls tests/input3/*`.text()).trim().split("\n").toSorted();

const tests = await Promise.all(
  files.map(async (inFile) => {
    const outFile = inFile.replace(/input/g, "output").replace(/in/g, "out");
    const inp = await fs.promises.readFile(inFile, { encoding: "utf8" });
    const out = await fs.promises.readFile(outFile, { encoding: "utf8" });
    return [false, inp.trim(), out.trim(), inFile];
  }),
);

function stringify(colorStyle, func) {
  return Object.defineProperty(String.prototype, colorStyle, {
    get: func,
    configurable: true,
  });
}

export const styles = {
  black: { open: "\u001b[30m", close: "\u001b[39m" },
  blue: { open: "\u001b[34m", close: "\u001b[39m" },
  bold: { open: "\u001b[1m", close: "\u001b[22m" },
  cyan: { open: "\u001b[36m", close: "\u001b[39m" },
  dim: { open: "\u001b[2m", close: "\u001b[22m" },
  gray: { open: "\u001b[90m", close: "\u001b[39m" },
  green: { open: "\u001b[32m", close: "\u001b[39m" },
  grey: { open: "\u001b[90m", close: "\u001b[39m" },
  red: { open: "\u001b[31m", close: "\u001b[39m" },
  reset: { open: "\u001b[0m", close: "\u001b[0m" },
  strikethrough: { open: "\u001b[9m", close: "\u001b[29m" },
  underline: { open: "\u001b[4m", close: "\u001b[24m" },
  white: { open: "\u001b[37m", close: "\u001b[39m" },
};
Object.keys(styles).forEach((styleName) => {
  stringify(styleName, function () {
    return color(this, styleName).toString();
  });
});
function color(str, styleName) {
  const code = styles[styleName];
  return code.open + str.replace(code.closeRe, code.open) + code.close;
}

let results = [];

const batches = tests.reduce((acc, v, i) => {
  if (i % 2000 == 0) {
    acc.push([]);
  }
  acc.at(-1).push(v);
  return acc;
}, []);
// batches.splice(10, 10e3);

let batchI = 0;
let runI = -1;
for (const batch of batches) {
  let timeoutId;
  const runPromises = batch.map(
    async ([isRegex, inp, expected, inFileName]) => {
      runI++;
      let myRunI = runI;
      results[myRunI] = [
        false,
        `${"x".red.bold} test ${inFileName}:\n${inp.slice(0, 150)}\n${"Timeout".white.bold}`,
      ];

      try {
        const res = (await $`./a < ${inFileName}`.text()).trim();
        let doesMatch;
        if (isRegex) {
          doesMatch = res.match(expected) !== null;
        } else {
          doesMatch = res == expected;
        }
        if (doesMatch) {
          results[myRunI] = [true, `${"√".green.bold} test ${inFileName}`];
        } else {
          results[myRunI] = [
            false,
            `${"x".red.bold} test ${inFileName}:\n${inp.slice(0, 150)}\n${"expected: ".white.bold} ${expected.slice(0, 150).blue.bold}\n${"got: ".white.bold} ${res.slice(0, 150).blue.bold}`,
          ];
        }
      } catch (e) {
        results[myRunI] = [
          false,
          `${"x".red.bold} test ${inFileName}:\n${inp.slice(0, 150)}\n${"Exit code:".white.bold} ${e.exitCode && e.exitCode.toString().red.bold}\n${e.stderr && e.stderr.toString().red.bold}`,
        ];
      }
    },
  );
  await Promise.race([
    Promise.all(runPromises),
    new Promise((resolve) => {
      timeoutId = setTimeout(() => {
        resolve();
      }, 10000);
    }),
  ]);
  clearTimeout(timeoutId);

  console.log(`Batch ${batchI} done out of ${batches.length}`);
  batchI++;
}

results = results.filter((r) => r);
results
  .sort((a, b) => ("" + a).localeCompare(b))
  .sort((a, b) => (b[0] ? 1 : -1) - [a[0] ? 1 : -1]);

for (const res of results) {
  if (!res[0]) console.log();
  console.log(res[1]);
}

console.log(`Passed: ${results.filter((r) => r[0]).length}/${results.length}`);
