document.addEventListener('DOMContentLoaded', function() {
    // when active class is clicked, scroll on top
    // navigation
    document.querySelector('.active').addEventListener('click', function() {
        window.scrollTo(0, 0);
    });

    const contactIcons = ['tele_ic', 'gh_ic', 'strv_ic', 'link_ic'];
    const name = ['Telegram', 'Github', 'Strava', 'LinkedIn'];

    const iconHover = document.querySelector('#icon-hover');

    for(let i = 0; i < contactIcons.length; i++) {
        var icon = document.querySelector('#' + contactIcons[i]);
        icon.addEventListener('mouseenter', function(e) {
            iconHover.innerHTML = '<i>Click to visit my ' + name[i] + ' account.<i>';
        });

        icon.addEventListener('mouseout', function(e) {
            iconHover.innerHTML = '<i>Page fin<i>';
        });
    }
});
