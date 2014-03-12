jQuery(function($) {
  // jQuery here
  $('.sbq_add_reply_btn.login_user').live("click", function(){
    $(this).parent('li').toggleClass('active');
    $(this).parents('.sbq_reply_actions').next('.sbq_reply_wrap').slideToggle(50);
    return false;
  });
  // $('.sbq_add_reply_btn.anonymous_no_comment').live("click", function(){
  //   alert('请登录后评论！');
  //   return false;
  // });
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

  $('.sbq_follow_btn a.flag-action').live("click", function() {
    var num = $('.sbq_follow_num a').html();
    num = parseInt(num)+1;
    $('.sbq_follow_num a').html(num);
  });

  $('.sbq_follow_btn a.unflag-action').live("click", function() {
    var num = $('.sbq_follow_num a').html();
    num = parseInt(num)-1;
    $('.sbq_follow_num a').html(num);
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

  // $(".captcha img").appendTo('.captcha .form-item-captcha-response');
  // $(".captcha .reload-captcha-wrapper a").appendTo('.captcha .form-item-captcha-response');
  $("#user-login-form #edit-captcha-response").attr("placeholder", "验证码");
  // $(".captcha").insertBefore('.sbq_checkbox_01');

  $('.field-name-field-message-video input[type="file"]').attr('accept', 'video/mp4');
  $('.field-name-field-message-voice input[type="file"]').attr('accept', 'audio/amr');
  $('.field-name-field-message-image input[type="file"]').attr('accept', 'image/png,image/gif,image/jpg,image/jpeg');
  $('.sbq_pm_icon .sbq_mp4 a').click(function(){
    $('.field-name-field-message-video input[type="file"]').click();
    return false;
  });
  $('.field-name-field-message-video input[type="file"]').change(function() {
    var file = $(this).val();
    var extension = file.substr( (file.lastIndexOf('.') +1) );
    if (extension == 'mp4') {
      $('.sbq_pm_editor textarea').attr('value', '视频:');
      $('.sbq_pm_editor form').submit();
    } else {
      alert('请选择mp4格式的视频文件');
      $('.sbq_pm_editor textarea').attr('value', '');
    }
  });

  $('.sbq_pm_icon .sbq_amr a').click(function(){
    $('.field-name-field-message-voice input[type="file"]').click();
    return false;
  });
  $('.field-name-field-message-voice input[type="file"]').change(function() {
    var file = $(this).val();
    var extension = file.substr( (file.lastIndexOf('.') +1) );
    if (extension == 'amr') {
      $('.sbq_pm_editor textarea').attr('value', '音频:');
      $('.sbq_pm_editor form').submit();
    } else {
      alert('请选择amr格式的音频文件');
      $('.sbq_pm_editor textarea').attr('value', '');
    }
  });

  $('.sbq_pm_icon .sbq_pic a').click(function(){
    $('.field-name-field-message-image input[type="file"]').click();
    return false;
  });
  $('.field-name-field-message-image input[type="file"]').change(function() {
    var file = $(this).val();
    var extension = file.substr( (file.lastIndexOf('.') +1) );
    if (extension == 'png' || extension == 'gif' || extension == 'jpg' || extension == 'jpeg') {
      $('.sbq_pm_editor textarea').attr('value', '图片:');
      $('.sbq_pm_editor form').submit();
    } else {
      alert('请选择png、gif、jpg、jpeg格式的音频文件');
      $('.sbq_pm_editor textarea').attr('value', '');
    }
  });

  $('form input').focus(function(){
    $(this).removeClass('error');
  });

  // center info page left menu
  if ($('body').hasClass('page-center-info')) {
    var menu = $("#block-views-sbq-center-blocks-menu .sbq_hospital_sub_nav");
    var menu_offset = menu.offset();
    var menu_top = menu_offset.top;
    // All list items
    var menuItems = menu.find("a");
    // Anchors corresponding to menu items
    var scrollItems = menuItems.map(function(){
      var item = $($(this).attr("href"));
      if (item.length) { return item; }
    });

    $(window).scroll(function() {
      if ($(window).scrollTop() > menu_top) {
        menu.css({"position": "fixed", "top": "10px"});
      } else {
        menu.css({"position": "relative", "top": "0px"});
      };
      // TODO: make the menu link active style
      // Get container scroll position
      var fromTop = $(this).scrollTop();

      // Get id of current scroll item
      var cur = scrollItems.map(function(){
        if ($(this).offset().top < fromTop+20)
          return this;
      });
      // Get the id of the current element
      cur = cur[cur.length-1];
      var id = cur && cur.length ? cur[0].id : "";
      // Set/remove active class
      menuItems
        .parent().removeClass("active")
        .end().filter("[href=#"+id+"]").parent().addClass("active");
    });
    $(".sbq_hospital_sub_nav li a").click(function() {
      var target = $($(this).attr("href"));
      var target_offset = target.offset();
      var target_top = target_offset.top;
      $('body,html').animate({
        scrollTop : target_top
      }, 500);
      return false;
    });
  };
});


(function($) {

/**
 * Live preview of Administration menu components.
 */
Drupal.behaviors.tiger = {
  attach: function (context, settings) {
    $('.sbq_pm_list .messages').ready(function(){
      setTimeout(function(){
        $('.sbq_pm_list .messages').hide();
      }, 3000);
    });

    $('#user-profile-form .user-picture a').click(function(){
      $('#edit-picture-upload').click();
      return false;
    });

    $('#user-register-form .form-type-textfield .description').hide();
    $('#user-register-form .form-type-textfield ').click(function(){
      $(this).children('.description').show();
    });
    $('#user-register-form .form-type-textfield input').blur(function(){
      var warning_str = '必须填写'+$(this).prev('label').text().replace('*','');
      if($(this).val() == '' && $(this).hasClass('required')) {
        $(this).parent('.form-type-textfield').children('.description').wrap('<span class="register_error"/>').text(warning_str);
      }else{
        $(this).parent('.form-type-textfield').children('.description').hide();
      };
    });

    $('#user-register-form .form-type-password input').blur(function(){
      var warning_str = '必须填写'+$(this).prev('label').text().replace('*','');
      if($(this).val() == '' && $(this).hasClass('required')) {
        //<span class="register_error"><div class="description" style="display: block;">必须填写邮箱 </div></span>
        if($(this).parent('.form-type-password').find('.description').length == 0) {
          $(this).parent('.form-type-password').wrap('<span class="register_error"/>').append('<div class="description" style="display: block;">'+warning_str+'</div>');
        }
        $(this).parent('.form-type-password').children('.register_error').show();
      }else{
        $(this).parent('.form-type-password').children('.register_error').hide();
      };
    });

    $('#user-register-form input').blur(function(){
      if(!($(this).val() == '')) {
        $(this).parent('.form-item').children('.register_error').hide();
        $(this).parent('.form-item').children('.description').hide();
      }else {
        $(this).parent('.form-item').children('.register_error').show();
        $(this).parent('.form-item').children('.description').show();
      }
    });

    $('#user-register-form .form-item-pass .description').hide();
    $('#user-register-form .password-field').blur(function(){
      $('#user-register-form .password-suggestions').hide();
    });

    //username min length 2
    //email

    $('#user-register-form .form-item-mail input').blur(function(){
      if(!($(this).val() == '')) {
        var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
        if(!regex.test($(this).val())) {
          $(this).parent('.form-item').find('.description').addClass('error_message').html('邮箱格式不正确');
          $(this).parent('.form-item').find('.description').show();
        }
      }
    });

    $('#user-register-form input.username').blur(function(){
      if($(this).val() != '' && $(this).val().length<2) {
        $(this).parent('.form-item').find('.description').addClass('error_message').html('用户名至少2个字符');
        $(this).parent('.form-item').find('.description').show();
      }
    });
    //form behaviors
    $('form .form-submit').click(function(e){
      $('input.required').each(function(){
        if($(this).val()==''){
          $(this).focus();
          e.preventDefault()
          return false;
        }
      });
    });

    $('#user-register-form input').live("mousedown",function(){
      $(this).parent('.form-item').children('.register_error').hide();
      $(this).parent('.form-item').children('.description').hide();
    });
   //  if(typeof(CKEDITOR) === 'object')
   //  CKEDITOR.on( 'dialogDefinition', function( ev )
   // {
   //    // Take the dialog name and its definition from the event
   //    // data.
   //    var dialogName = ev.data.name;
   //    var dialogDefinition = ev.data.definition;

   //    // Check if the definition is from the dialog we're
   //    // interested on (the Link and Image dialog).
   //    if (dialogName == 'image' )
   //    {
   //       // remove Upload tab
   //       dialogDefinition.removeContents( 'advanced' );
   //       dialogDefinition.removeContents( 'target' );
   //       dialogDefinition.removeContents( 'Link' );


   //        // dialogDefinition.onShow = function () {
   //        //   // This code will open the Advanced tab.
   //        //   this.selectPage('Upload');
   //        // };
   //    }

   //    if ( dialogName == 'link') {
   //       // remove Upload tab
   //       dialogDefinition.removeContents( 'advanced' );
   //       dialogDefinition.removeContents( 'Upload' );
   //       dialogDefinition.removeContents( 'upload' );
   //       dialogDefinition.removeContents( 'target' );
   //    }

   // });

  $('form input[name*=field_phone]').each(function(){
    value = $(this).val();
    var partten = /^0?1[3|4|5|8][0-9]\d{8}$/;
    if(!partten.test(value)) {
      alert('手机号码填写不正确!');
    }
  });


  }
};


})(jQuery);
