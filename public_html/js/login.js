$( document ).ready(function () {

    // when write stuffs in login fields
    $('#username, #password').on('input', function(){

        // if both username and password fields have letters
        if ($('#username').val() && $('#password').val()){

            // make submit button look active
            $('#enter').addClass('enterActive');
        }

        // or else, make submit button look inactive
        else {
            $('#enter').removeClass('enterActive');
        }
    });


    // only POST form when usernand and password are not empty
    $('#loginForm').submit(function(){
        if (!($('#username').val() && $('#password').val())) return false;
    });


});