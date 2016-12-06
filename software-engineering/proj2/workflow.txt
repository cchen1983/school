/* Yihang Zhao @ 2016.09.03
 * Workflow JS:
 *   Perparing working forms
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
    function reg_form_get(e) {
        /*Form Rendering*/
        $.ajax({
            type: "GET",
            url: "/workflow/reg-form-view/",
            data: e.data,
            success: function(html) {
                $("#" + e.data.cls + "-reg-view").html(html);
            }
        });
    }

    $('#btn_prc_new').click({"type": "prc_new", "cls": "prc"},reg_form_get);
    $('#btn_memb_new').click({"type": "mem_new", "cls": "mem"},reg_form_get);
    $('#btn_memb_recharge').click({"type": "mem_rec", "cls": "mem"}, reg_form_get);
    $('#btn_exp_product').click({"type": "exp_prod", "cls": "exp"}, reg_form_get);
    $('#btn_exp_other').click({"type": "exp_other", "cls": "exp"}, reg_form_get);
    $('#btn_act_promo').click({"type": "act_promo", "cls": "act"}, reg_form_get);
    $('#btn_act_discount').click({"type": "act_discount", "cls": "act"}, reg_form_get);
});
