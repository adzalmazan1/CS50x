// TODO: Add code to check answers to questions
document.addEventListener('DOMContentLoaded', function() {
    const crct = document.querySelector('#crct'), inc = document.querySelectorAll('.inc'); // querySelectorAll
    const p1 = document.querySelector('#p1Status'), p2 = document.querySelector('#p2Status');

    // Correct button turns green when clicked
    crct.addEventListener('click', function() {
        crct.style.backgroundColor = "green";
        p1.innerHTML = 'Correct';
    });


    // Incorrect button turns red when clicked
    for(let i = 0; i < inc.length; i++) {
        inc[i].addEventListener('click', function() {
            inc[i].style.backgroundColor = "red";
            p1.innerHTML = 'Incorrect';
        });
    }

    const form = document.querySelector('form');
    form.addEventListener('submit', function(e) {
        const ans = document.getElementById('ans').value.toLowerCase(); // only take the value of ans on 'submit' -- listening for submit event
        if(ans.localeCompare('philippines') == 0) {
            p2.innerHTML = 'Correct';
        }
        else {
            p2.innerHTML = 'Incorrect';
        }
        e.preventDefault();
    });
});
