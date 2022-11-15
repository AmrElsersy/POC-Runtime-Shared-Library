console.log("renderer start", document.getElementById("submit_btn"));

document.getElementById("submit_btn").addEventListener("click", function(event) {
    event.preventDefault();    //stop form from submitting
    var num1 = document.getElementById("first_num").value;
    var num2 = document.getElementById("second_num").value;
    if (num1 && num2)
    {
        var nums_str = num1 + "," + num2;
        window.electronAPI.sendAddData(nums_str);
    }
});