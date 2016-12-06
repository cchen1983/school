/* cchen @ 2016.09.01
 * User Account Login/Signup
 */
function getCookie(name) {
    var cookieValue = null;
    if (document.cookie && document.cookie != '') {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = jQuery.trim(cookies[i]);
            if (cookie.substring(0, name.length + 1) == (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}

var csrftoken = getCookie('csrftoken');

function csrfSafeMethod(method) {
    return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

//CSRF Protection: csrf token insert
$.ajaxSetup({
    beforeSend: function(xhr, settings) {
        if (!csrfSafeMethod(settings.type) && !this.crossDomain) {
            xhr.setRequestHeader("X-CSRFToken", csrftoken);
        }
    }
});

$(function() {

    /*show up*/
    $(".login_required").fancybox({
        href:   '/login/',
        type:   'ajax',

        /* style */
        width:  500,
        //Height: 600,
        fitToView:  false,
        //autoSize:   false,

        /*cchen Notes: fancybox content could only be selected after show, 
        *jquery object or doms are not ready at the timing of afterLoad*/
        afterShow:  function() {
           hook();
        },

        afterClose: function() {
            if ($.fancybox.login_ok) {
                window.location = $.fancybox.next;
            }
        }
    });

    $(".login_required").click(function(e){
        /*hold on the original request*/
        $.fancybox.next = $(this).attr('href');
    });
 
    /*callbacks*/ 
    function hook() {

        $(".btn").click(function(){
            this.blur();    //remove focus
        });

        /*submit*/
        $("#login_form").submit(function(){
            $.ajax({
                type:   "POST",
                url:    "/login/",
                data:   $("#login_form").serialize(),

                success:    function(html) {
                    resp = $.trim(html)
                    if (resp == "OK") {
                        $.fancybox.login_ok = true;
                        $.fancybox.close();
                    }
                    else if (resp == "DISABLED") {
                        $("#login_error").text("The specified user has been disabled.");
                        $("#login_error").show();
                        $.fancybox.update();
                    }
                    else {
                        $("[name=password]").val("");
                        $("#login_error").text("Invalid user or password.");
                        $("#login_error").show();
                        $.fancybox.update();
                    }
                }

            });           
            return false; 
        });        

        $("#register_form").submit(function(){
            user = $("[name=newusername]").val();
            pwd = $("[name=npassword]").val();
            email = $("[name=email]").val();
            cpwd = $("[name=cpassword]").val();
            valid = true;

            if (user == "" || pwd == "" || email == "" || cpwd == "") {
                $("#register_error").text("Please fill all field.");
                $("#register_error").show();
                valid = false;
            }

            if (pwd != cpwd) {
                $("[name=password]").val("");
                $("[name=cpassword]").val("");
                $("#mismatch_error").show();
                valid = false;
            }
            else {
                $("#mismatch_error").hide();
            }

            if (!valid) {
                $.fancybox.update();
            }
            else {
                $.ajax({
                    type:   "POST",
                    url:    "/login/",
                    data:   $("#register_form").serialize(),

                    success:    function(html) {
                        emsg = "";
                        switch ($.trim(html)) {
                            case "OK":
                                $.fancybox.login_ok = true;
                                break;
                            case "USER_EXIST":
                                emsg = "Username has existed.";
                                break;
                            case "EMAIL_EXIST":
                                emsg = "Email has existed.";
                                break;
                            case "EMAIL_INVALID":
                                emsg = "Invalid email address.";
                                break;
                            default:
                                emsg = "Unknown error.";
                        }

                        if (emsg == "") {
                            $.fancybox.close();
                        }
                        else {
                            $("#register_error").text(emsg);
                            $("#register_error").show();
                            $.fancybox.update();
                        }
                    } 

                });
            }
            return false;
        });  //end register-form submit
    
    }

});
