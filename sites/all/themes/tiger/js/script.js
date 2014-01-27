jQuery(function($) {
  // jQuery here
  $('.sbq_add_reply_btn.login_user').live("click", function(){
    $(this).parent('li').toggleClass('active');
    $(this).parents('.sbq_reply_actions').next('.sbq_reply_wrap').slideToggle(50);
    return false;
  });
  $('.sbq_add_reply_btn.anonymous_no_comment').live("click", function(){
    alert('请登录后评论！');
    return false;
  });
  reply_hidden = true;
  $('.sbq_add_reply_btn.anonymous_comments').live("click", function(){
    $(this).parent('li').toggleClass('active');
    $(this).parents('.sbq_reply_actions').next('.sbq_reply_wrap').slideToggle(50, function() {
      if (reply_hidden) {
        alert('请登录后评论！');
        reply_hidden = false;
      } else{
        reply_hidden = true;
      };
    });
    return false;
  });

  $('.ckeditor_links').hide();

  $('.sbq_all_reply_btn a').live("click", function() {
    $(this).html('加载中...');
    var nid = $(this).attr('nid');
    var load_url = '/ajax/comments/'+nid;
    var all_reply_btn = $(this).parents('.sbq_all_reply_btn');
    var replace_ul = $("#comments-"+nid+" ul");
    $.ajax({
      url: load_url,
      dataType: "json",
      type: "GET",
      success: function(data){
      var transform = {"tag":"li","children":[
        {"tag":"div","class":"sbq_user_pic","html":"${sbq_user_pic}"},
        {"tag":"div","class":"sbq_reply_list_content","children":[
            {"tag":"div","class":"sbq_user_name","html":"${sbq_user_name}"},
            {"tag":"div","class":"sbq_text","html":"${sbq_text}"},
            {"tag":"div","class":"sbq_date","html":"${sbq_date}"}
          ]}
        ]};
        replace_ul.html('');
        replace_ul.json2html(data,transform);
        all_reply_btn.hide();
      }
    });
    return false;
  });

  $('.sbq_follow_num a').live("click", function() {
    var follow_list_ul = $(".sbq_follow_list ul");
    if (follow_list_ul.hasClass('loaded')) {
      $('.sbq_follow_list_ul').slideToggle();
    } else{
      var nid = $(this).attr('nid');
      var load_url = '/ajax/follower/'+nid;
      var all_reply_btn = $(this).parents('.sbq_follow_num');
      $.ajax({
        url: load_url,
        dataType: "json",
        type: "GET",
        success: function(data){
          var transform = {"tag":"li","html":"${sbq_user_pic}"};
          follow_list_ul.addClass('loaded');
          follow_list_ul.json2html(data,transform);
        }
      });
    };
    return false;
  });

  $(".captcha img").appendTo('.captcha .form-item-captcha-response');
  $(".captcha .reload-captcha-wrapper a").appendTo('.captcha .form-item-captcha-response');
  $("#user-login-form #edit-captcha-response").attr("placeholder", "验证码");
  $(".captcha").insertBefore('.sbq_checkbox_01');

});


(function($) {

/**
 * Live preview of Administration menu components.
 */
Drupal.behaviors.tiger = {
  attach: function (context, settings) {
    $('#user-profile-form .user-picture').click(function(){
        $('#edit-picture-upload').click();
        return false;
      });
    $('#user-register-form .form-type-textfield .description').hide()
    $('#user-register-form .form-type-textfield ').click(function(){
      $(this).children('.description').show();
    });
    $('#user-register-form .form-type-textfield input').blur(function(){
      $(this).parent('.form-type-textfield').children('.description').hide();
    });
    $('#user-register-form .form-item-pass .description').hide();
    $('#user-register-form .password-field').blur(function(){
      $('#user-register-form .password-suggestions').hide();
    });

    $('form .form-submit').click(function(e){      
      $('input.required').each(function(){
        if($(this).val()==''){
          $(this).focus();
          e.preventDefault()
          return false; 
        }
      });
    });

  }
};


})(jQuery);
