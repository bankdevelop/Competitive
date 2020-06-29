const readline = require('readline');

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

var i = 0;
var max = 0;
var data = [];
rl.on("line", function(line) {
   
    if(max===0) {
        max = parseInt(line)*2;
    }else{
        data.push(line);
        i++
    }
   
    if(i>=max) rl.close();
});