jQuery(function($) {
    $('.alert-block a.close').click(function() {
        $(this).parents('.alert-block').hide();
    });
    $('.node-type-sbq-topic textarea').focus(function() {
        $(this).attr('value', '');
    });
    $('.user_doctor_register_ajax').click(function() {
        var href = $(this).attr('href');
        if ($('#sbq_doctor_quick_register').length > 0) {
             $('#sbq_doctor_quick_register').show();
        } else {
            var self = $(this);
            self.parent().parent().find("li.first").append('<div id="status" style="background: url(/misc/throbber.gif) no-repeat 5px -16px; width:21px; height:16px;display: inline-block;"> </div>');
            $.get(href + '?ajax=true', function(data) {
                self.parent().parent().find("li #status").remove()
                $('body').append(data);
                $('section #block-user-login').clone().appendTo('#sbq_doctor_quick_register .modal-body');
                $('#sbq_doctor_quick_register #user-login-form div.item-list:first').remove();
               // $('#sbq_doctor_quick_register').hide();
                //  $(data).modal();
            });
        }
        return false;
    })
    // 注册同意服务条款
    $('#user-register-form #edit-submit').live('click', function() {
        if ($('#user-register-form #edit-agree').is(':checked')) {
            return true;
        }
        alert('请同意伤不起服务条款');
        return  false;
    })

    // 用户关系请求
    $('.relationship_ajax_action').live('click', function() {
        var self = $(this);
        self.append('<div id="status" style="background: url(/misc/throbber.gif) no-repeat 5px -16px; width:21px; height:16px;display: inline-block;"> </div>');
        $.getJSON(self.attr('href') + '?ajax=true', function(data) {
            $('#sbq_commons_user_relationship_view').replaceWith(data['html']);
        })
        return false;
    })
    Drupal.behaviors.sbq_commons = {
        attach: function(context, settings) {
            $('.alert-block a.close').click(function() {
                $(this).parents('.alert-block').hide();
            });

            $('.node-type-sbq-topic textarea').focus(function() {
                $(this).attr('value', '');
            });
        }
    }
});

