
$( document ).ready(function () {

    // return whether or not all required fields are filled
    function fieldsFilled(){
        return ($('#fullname').val() && $('#username').val() && $('#password').val() && $('#password2').val());
    }

    // return whether the 2 password fields match
    function passwordMatch(){
        return ($('#password').val() == $('#password2').val());
    }

    // when write stuffs in login fields
    $('#fullname, #username, #password, #password2').on('input', function(){

        // if all fields are filled
        if (fieldsFilled()){

            // make submit button look active
            $('#enter').addClass('enterActive');
        }

        // or else, make submit button look inactive
        else {
            $('#enter').removeClass('enterActive');
        }
    });


    // submit form
    $('#signupForm').submit(function(){

        // don't submit if there're fields are not filled
        if (!fieldsFilled()) return false;

        // don't submit if password don't match
        if (!passwordMatch()) return false;
    });


});