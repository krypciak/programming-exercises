import { $ } from "bun";
const files = (await $`ls in*`.text()).trim().split("\n").toSorted();

const tests = await Promise.all(
  files.map(async (file) => {
    const cont = await $`cat ./${file}`.text();
    let split = "@EXPECTED";
    let isRegex = false;
    if (cont.includes("@EXPECTED REGEX")) {
      split = "@EXPECTED REGEX";
      isRegex = true;
    }
    const [inp, expected] = cont.split(split);
    return [isRegex, inp.trim(), expected.trim()];
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

const results = [];
await Promise.all(
  tests.map(async ([isRegex, inp, expected], i) => {
    try {
      const res = (await $`./a < ${new Response(inp)}`.text()).trim();
      let doesMatch;
      if (isRegex) {
        doesMatch = res.match(expected) !== null;
      } else {
        doesMatch = res == expected;
      }
      if (doesMatch) {
        results.push([true, `${"√".green.bold} test ${i}`]);
      } else {
        results.push([
          false,
          `${"x".red.bold} test ${i}:\n${inp.trim().slice(0, 150)}\n${"expected: ".white.bold} ${expected.slice(0, 150).blue.bold}\n${"got: ".white.bold} ${res.slice(0, 150).blue.bold}`,
        ]);
      }
    } catch (e) {
      results.push([
        false,
        `${"x".red.bold} test ${i}:\n${inp.trim().slice(0, 150)}\n${"Exit code:".white.bold} ${e.exitCode.toString().red.bold}\n${e.stderr.toString().red.bold}`,
      ]);
    }
  }),
);
results
  .sort((a, b) => ("" + a).localeCompare(b))
  .sort((a, b) => (b[0] ? 1 : -1) - [a[0] ? 1 : -1]);

for (const res of results) {
  if (!res[0]) console.log();
  console.log(res[1]);
}
