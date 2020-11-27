const getHashTags = (str) => {
	// Implement your solution within this function
    var arr = str.split(' ');
    var cloneArr = arr.slice();
    arr.sort(function(a, b){
        if (b.length == a.length){
            var indexB = cloneArr.indexOf(b);
            var indexA = cloneArr.indexOf(a);
            return indexA-indexB;
        }
        return b.length-a.length;
    });

    if (arr.length <= 3) {
        return arr.map(x => '#'+x.toLowerCase());
    }

    var returnArr = [];
    for(let i=0; i<3; i++){
        returnArr.push(arr[i]);
    }
    return returnArr.map(x => '#'+x.toLowerCase());
}

module.exports = {
    getHashTags,
}

console.log(getHashTags("Visualizing Science"));