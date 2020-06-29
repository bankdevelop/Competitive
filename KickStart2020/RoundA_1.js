const readline = require('readline');
const { WSAEHOSTDOWN } = require('constants');

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

var n = 0, i = 0;
var input = [], output = [], canBuy = 0;
var nHouse = 0, budget = 0, testRound = 1;

//input
rl.on("line", function(line) {

    if(n==0) n=parseInt(line)*2;
   
    if(i%2==0) {
        arr = line.split(" ");
        nHouse = parseInt(arr[0]);
        budget = parseInt(arr[1]);
    }else{
        houses = line.split(" ");
        e = 0;
        while( e++ < nHouse ) {
          num = parseInt(houses[e]);
          if(input.length == 0) input.push(num);
          else {
            if( num >= input[e-1] ){
              input.push(num);
            }else{
              j = e;
              while(j>0){
                if(num > input[j-1]){
                  g = input.length;
                  while(g>j-1){
                    input[g] = input[g-1];
                    g--;
                  }
                  input[j-1] = num;
                  break;
                }
                j--;
              }
              if(j==0) input = [num, ...input];
            }
          }
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

        console.log(`Case #${testRound}: ${canBuy}`);
        output.push(`Case #${testRound++}: ${canBuy}`);
    }
    if(i++>=n) rl.close();
});

var nOutput = output.length;
var k = 0;
while( k < nOutput ){
  console.log(output[k]);
  k++;
}

//asynchronous problem all while loop run at the same time