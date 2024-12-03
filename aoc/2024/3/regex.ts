// @ts-expect-error
import * as fs from "fs";
const data: string = await fs.promises.readFile("in0", "utf8");

let firstPart = true;

const matches = [
  ...data.matchAll(/don't\(\)|do\(\)|mul\((\d\d?\d?),(\d\d?\d?)\)/g),
];
let add = true;
const res = matches.reduce((acc, v) => {
  if (v[0] == "do()") add = true;
  else if (v[0] == "don't()") add = false || firstPart;
  else if (add) acc += Number(v[1]) * Number(v[2]);

  return acc;
}, 0);

console.log(res);
