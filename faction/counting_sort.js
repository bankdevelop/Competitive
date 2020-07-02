const test = [1,30,25,60,380,890,870,560,9870,54,66];

let countingSort = (arr, min, max) => {
    let i = min,
        j = 0,
        len = arr.length,
        count = [];
    for (i; i <= max; i++) {
        count[i] = 0;
    }
    for (i = 0; i < len; i++) {
        count[arr[i]] += 1;
    }
    for (i = min; i <= max; i++) {
        while (count[i] > 0) {
            arr[j] = i;
            j++;
            count[i]--;
        }
    }
    return arr;
};

console.log(countingSort(test, 1, 9870));