/* Saheed @ 2016.09.06
 * Query: Advance searching and editing of Data Models 
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
    function tbl_sel_query() {
        tblName = $("#tbl_sel").val();
        $.ajax({
            type: "POST",
            url: "/query/get-meta/",
            data: {"tblName" : tblName},

            success: function(data) {
                $("#fd_sel").empty(); /*Clear previous records*/
                for (var i in data){
                    $("#fd_sel").append($("<option/>", {value:data[i], text:data[i]}));
                }
                console.log($("#fd_sel"));
                $("#query_submit").show() 
            }
        });
    }

    $("#tbl_sel").change(tbl_sel_query);

    $('#query_form').submit(function(e) {
        $.ajax({
            type: "POST",
            url: "/query/cond-query/",
            data: $(this).serialize(),
            
            success: function(html) {
                $("#table_view").html(html);
            }
        });        

        return false;
    });
});
