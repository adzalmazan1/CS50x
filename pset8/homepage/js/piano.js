document.addEventListener('DOMContentLoaded', function() {
    // Selecting all elements of class black and white key
    // When you use document.querySelectorAll(), it returns a NodeList (not a true array)
    var wkList = document.querySelectorAll('.white-key');
    var bkList = document.querySelectorAll('.black-key');

    // Array.from() is a built-in JavaScript method that creates a new array from NodeList etc.
    var comb = Array.from(wkList).concat(Array.from(bkList));

    // number of sections to be made
    var Education = [
        '[2017 - 2021] Allen National High School — Science, Technology, and Engineering (STE)',
        '[2021 - 2023] University of the East — Science, Technology, Engineering, and Mathematics (STEM)',
        '[2023 - Present] University of the Philippines — BS in Computer Science (BSCS)',
    ];

    var Experience = [
        '[2017 - Present] Freelance — Video Editor',
        '[2022 - 2022] Samuel Digital — Lead Acquisition Specialist',
        '[2023 - 2023] Samuel Digital — Social Media Manager',
    ];

    var Interests = [
        'All sorts of burgers',
        'Cycling',
        'Badminton',
        'Comedy / Mystery',
        'Jazz / Neo soul / R&B',
        'Jogging',
        'Musical Instruments',
    ];

    var sections = [Education, Experience, Interests];
    var spacedTitle = ['E D U C A T I O N', 'E X P E R I E N C E', 'I N T E R E S T S'];

    // Selecting aboutTitle and aboutList to be modified
    var aboutTitle = document.querySelector('#about-title');
    var aboutList = document.querySelector('#about-list');

    function aboutTitleDefault(spacedTitle) {
        // setting the attribute
        aboutTitle.setAttribute('style', 'margin: 16px 0 16px 0');

        // checking if it's NULL
        if(aboutList != null) {
            aboutList.innerHTML = '';
        }

        aboutTitle.textContent = spacedTitle;
    }

    function aboutListDefault(specList) {
        for(let i = 0; i < specList.length; i++) {
            var newList = document.createElement('li');
            var textNode = document.createTextNode(specList[i]);
            newList.appendChild(textNode);

            newList.setAttribute('style', 'margin-bottom: 10px');

            aboutList.appendChild(newList);
        }
    }

    function educInfo() {
        aboutTitleDefault(spacedTitle[0]);
        aboutListDefault(Education);
    }

    function expInfo() {
        aboutTitleDefault(spacedTitle[1]);
        aboutListDefault(Experience);
    }

    function interestsInfo() {
        aboutTitleDefault(spacedTitle[2]);
        aboutListDefault(Interests);
    }

    var functionForKeys = [educInfo, expInfo, interestsInfo];

    // Selecting active keys
    var listOfUsed = [];
    for(let i = 0; i < sections.length; i++) {
        // Returns a random integer from 0 to 11
        do {
            var randNum = Math.floor(Math.random() * comb.length);
        } while(listOfUsed.includes(randNum));

        listOfUsed.push(randNum);

        comb[randNum].addEventListener('click', function(e) {
            this.setAttribute('style', 'background: #c4643f;');

            // reset the color after a short delay
            setTimeout(() => {
            e.target.style.background = "";
            }, 1500);

        });

        comb[randNum].addEventListener('click', functionForKeys[i]);
    }
});


