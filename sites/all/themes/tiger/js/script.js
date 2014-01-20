jQuery(function($) {
  // jQuery here
  $('.sbq_add_reply_btn').live("click", function(){
    $(this).parent('li').toggleClass('active');
    $(this).parents('.sbq_reply_actions').next('.sbq_reply_wrap').slideToggle(50);
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

  // End of jQuery
  Drupal.behaviors.tiger = {
    attach: function (context, settings) {
      // behaviors here

      // End of behaviors
    }
  };
});
