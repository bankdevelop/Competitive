const readline = require('readline');

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

var n = 0, i = 0;
var output = [], canBuy = 0;
var nHouse = 0, budget = 0, testRound = 1;

var countingSort = (arr, min, max) => {
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


//input
(new Promise((resolve, reject) => {
		rl.on("line", function(line) {

			if(n===0) n=parseInt(line)*2;
			else{
				if(i%2===0) {
					arr = line.split(" ");
					nHouse = parseInt(arr[0]);
					budget = parseInt(arr[1]);
				}else{
					houses = line.split` `.map(x=>+x)
					houses = countingSort(houses, (Math.min(...houses)), Math.max(...houses));

					//output
					let p = 0;
					while( p < nHouse ){
						if( (result=budget-houses[p++])>=0 ) {
							budget=result;
							canBuy++;
						}else{
							break;
						}
					}
					
					output.push(`Case #${testRound++}: ${canBuy}`);
				}

				if(++i>=n) {
					resolve();
					rl.close();
				}

				//reset value
				canBuy = 0;
			}
			
		});
	})
).then(()=>{
	var nOutput = output.length;
	var k = 0;
	while( k < nOutput ){
	  console.log(output[k]);
	  k++;
	}
});

//PASS