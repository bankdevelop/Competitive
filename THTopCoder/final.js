const getHashTags = (str) => {
	// Implement your solution within this function
    var arr = str.replace(/[.,\/#!$%\^&\*\'\[\]\?\";:{}=\-_`~()]/g,"")
				 .split(' ')
				 .filter((y) => y !== '');
    var cloneArr = arr.slice();

    if (arr.length < 3) {
		arr.sort(function(a, b){
			return b.length-a.length;
		});
        return arr.map(x => `#${x.toLowerCase()}`);
    }

    arr.sort(function(a, b){
        if (b.length == a.length){
            var indexB = cloneArr.indexOf(b);
            var indexA = cloneArr.indexOf(a);
            return indexA-indexB;
        }
        return b.length-a.length;
    });
	
    var returnArr = [];
    for(let i=0; i<3; i++){
        returnArr.push(arr[i]);
    }
    return returnArr.map(x => `#${x.toLowerCase()}`);
}

module.exports = {
    getHashTags,
}

//----------------------------------------------------

const bucketize = (phrase, n) => {
	// Implement your solution in this function
    var words = phrase.split(' ');
	var tmp = words[0];
	var result = [];
	
    for(let i=1; i<words.length; i++){
		if(tmp.length > n) return [];
        if(`${tmp} ${words[i]}`.length > n){
            result.push(tmp);
			tmp = words[i];
        }else{
            tmp = `${tmp} ${words[i]}`;
        }
    }
	
	result.push(tmp);
    return result;
}

module.exports = {
    bucketize,
}

//----------------------------------------------------

const numToEng = (n) => {
    var oD = ['zero','one','two','three','four', 'five','six','seven','eight','nine'];
    var tD = ['ten','eleven','twelve','thirteen', 'fourteen','fifteen','sixteen', 'seventeen','eighteen','nineteen'];
	var wD = ['twenty','thirty','forty','fifty', 'sixty','seventy','eighty','ninety'];
	var hD = ['one hundred','two hundred','three hundred','four hundred', 'five hundred','six hundred','seven hundred','eight hundred', 'nine hundred'];
	if (n < 10) return oD[n];
	if (n < 20) return tD[n-10];
	if (n < 100 && n%10===0) return wD[n/10-2];
	if (n < 100) return `${wD[parseInt(n/10 - 2)]} ${numToEng(n%10)}`;
	if (n < 1000 && n%100===0) return hD[n/100-1];
	return `${hD[parseInt(n/100 - 1)]} ${numToEng(n%100)}`;
}

module.exports = {
    numToEng,
}
//---------------------------------------------------------
function getSubsets(arr, num) {
	var result = [[]];
	for (x of arr){
		var length = result.length;
		var i =0;

		while(i < length){
			var temp = result[i].slice(0);
			temp.push(x);
			result.push(temp);
			i++;
		}
	}
	return result.filter(x => x.reduce((a, b) => a + b, 0) === num)
				 .sort(function(a, b){
					 if (a.length === b.length){
						for(let i=0; i<a.length; i++){
							if (a[i]-b[i] !== 0)
								return a[i]-b[i];
						} 
					 }
					 return a.length-b.length;
				 });
}




