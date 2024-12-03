import { $ } from "bun";
import * as fs from "fs";
const files = (await $`ls tests/input1/*`.text()).trim().split("\n").toSorted();

const tests = await Promise.all(
  files.map(async (inFile) => {
    const outFile = inFile.replace(/input/g, "output").replace(/in/g, "out");
    const inp = await fs.promises.readFile(inFile, { encoding: 'utf8' });
    const out = await fs.promises.readFile(outFile, { encoding: 'utf8' });
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

const results = tests.map((t, i) => [
  false,
  `${"x".red.bold} test ${i}:\n${t[1].trim().slice(0, 150)}\n${"Timeout".white.bold}`,
]);

const timeoutPromise = new Promise((resolve) => {
  setTimeout(() => {
    resolve();
  }, 10000);
});

await Promise.race([
  Promise.all(
    tests.map(async ([isRegex, inp, expected, inFileName], i) => {
      try {
        const res = (await $`./a < ${new Response(inp)}`.text()).trim();
        let doesMatch;
        if (isRegex) {
          doesMatch = res.match(expected) !== null;
        } else {
          doesMatch = res == expected;
        }
        if (doesMatch) {
          results[i] = [true, `${"√".green.bold} test ${inFileName}`];
        } else {
          results[i] = [
            false,
            `${"x".red.bold} test ${inFileName}:\n${inp.trim().slice(0, 150)}\n${"expected: ".white.bold} ${expected.slice(0, 150).blue.bold}\n${"got: ".white.bold} ${res.slice(0, 150).blue.bold}`,
          ];
        }
      } catch (e) {
        results[i] = [
          false,
          `${"x".red.bold} test ${inFileName}:\n${inp.trim().slice(0, 150)}\n${"Exit code:".white.bold} ${e.exitCode.toString().red.bold}\n${e.stderr.toString().red.bold}`,
        ];
      }
    }),
  ),
  timeoutPromise,
]);

results
  .sort((a, b) => ("" + a).localeCompare(b))
  .sort((a, b) => (b[0] ? 1 : -1) - [a[0] ? 1 : -1]);

for (const res of results) {
  if (!res[0]) console.log();
  console.log(res[1]);
}

console.log(`Passed: ${results.filter((r) => r[0]).length}/${results.length}`);
