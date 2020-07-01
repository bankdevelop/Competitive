const readline = require('readline');

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

var n = 0, i = 0;
var input = [], output = [], canBuy = 0;
var nHouse = 0, budget = 0, testRound = 1;

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
					houses = line.split(" ");
					nInput = 0;
					//insertion sort
					while( nInput < nHouse ) {
						num = parseInt(houses[nInput]);
						if(input.length === 0) {
							input.push(num);
						} else {
							if( num >= input[nInput-1] ){
								input.push(num);
							}else{
								j = nInput-1;
								while(j>0){
									if(num > input[j-1]){
										g = nInput;
										while(g>j){
											input[g] = input[g-1];
											g--;
										}
										input[j] = num;
										break;
									}
									j--;
								}
								if(j===0) input = [num, ...input];
							}
							console.log(input);
						}
						nInput++;
					}

					//output
					let p = 0;
					while( p < nHouse ){
						if( (result=budget-input[p++])>=0 ) {
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
				input = [], canBuy = 0;
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

//result : Sample Failed: WA