document.addEventListener('DOMContentLoaded', function() {
    // Country droplist
    var selectedCountries = ['Greece', 'Argentina', 'Japan', 'United States', 'Philippines'];

    // select <ul> with id #countryList
    const countryListContainer = document.querySelector("#countryList");

    for(let i = 0; i < selectedCountries.length; i++) {
        // create new list
        const newList = document.createElement("li");
        newList.innerHTML = ('<button class="dropdown-item">' + selectedCountries[i] + '</button>'); // for escaping purposes

        newList.setAttribute('id', 'elem' + i);

        // append new list to
        countryListContainer.appendChild(newList);

        document.querySelector('#elem' + i).addEventListener('click', function() {
            document.querySelector('#country').textContent = selectedCountries[i];
        });
    }

    // when formSubmit id is clicked, alert + ...
    document.querySelector('#formSubmit').addEventListener('click', function() {
        console.log(document.querySelector('#firstName').value);
        console.log(document.querySelector('#lastName').value);
        console.log(document.querySelector('#emailAdd').value);
        console.log(document.querySelector('#country').textContent);
        console.log(document.querySelector('#messageBody').value);

        // window.open('https://mail.google.com/mail/u/0/#inbox?compose=new');

        alert('Form successfully submitted');
    });
});
