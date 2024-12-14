// prettier-ignore
const arr = [
]

let lastIndexArr = []
console.log("0,");
for (let bajTarget = 1; bajTarget <= 1000; bajTarget++) {
  let vals = [];
  for (let i = 0; i < arr.length; i++) {
    const pairArr = arr[i];
    let bajRes;
    for (let j = Math.max(0, lastIndexArr[i] ?? 0); j < pairArr.length; j++) {
      const [baj, num] = pairArr[j]

      if (baj > bajTarget) {
	      lastIndexArr[i] = j - 3;
	break;
      }
      bajRes = num;
    }
    vals.push(bajRes);
  }
  vals.sort((a, b) => (a < b ? -1 : a > b ? 1 : 0));

  const low50 = vals[Math.floor(vals.length * 0.001)];
  console.log(`${low50},`);
}
