/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {


// To understand behaviors, see https://drupal.org/node/756722#behaviors
Drupal.behaviors.my_custom_behavior = {
  attach: function(context, settings) {
  	//alert('test-请删除本行，从本行开始添加js！注意封装、及用途注释。谢谢~');
    // Place your code here.
    $('#secondary-menu a').each(function() {
      var link = $(this).attr('href');
      if (link.indexOf("customer") >=0) {
        $(this).attr('href', '#');
        $(this).attr('data-toggle', 'modal');
        $(this).attr('data-target', '#sbq_customer_register_form_modal');
      };
      if (link.indexOf("doctor") >=0) {
        $(this).attr('href', '#');
        $(this).attr('data-toggle', 'modal');
        $(this).attr('data-target', '#sbq_doctor_register_form_modal');
      };
      if (link.indexOf("login") >=0) {
        $(this).attr('href', '#');
        $(this).attr('data-toggle', 'modal');
        $(this).attr('data-target', '#sbq_user_login_form_modal');
      };

    });

    $('#myCarousel').carousel({
		  interval: 4000
		})
    $('#sbq-user-carousel').carousel({
      interval: 5000
    })
    /*个人中心滚动监听*/
    $('#block-sbq-commons-sbq-user-menu ul').addClass('nav');;
    $('body.section-users').attr({'data-spy':'scroll','data-target':'#block-sbq-commons-sbq-user-menu'})
    if($('body.section-users').length>0){
      $.fn.fixedDiv = function(actCls){
        var pos = 0,
            that = $(this),
            topVal;

        if(that.length > 0){
            topVal = that.offset().top;
        }

        function fix(){
            pos = $(document).scrollTop();

            if (pos > topVal) {
                that.addClass(actCls);
                if (!window.XMLHttpRequest) {
                    that.css({
                        position: 'absolute',
                        top     : pos
                    });
                }
            } else {
                that.removeClass(actCls);
                if (!window.XMLHttpRequest) {
                    that.css({
                        position: 'static',
                        top     : 'auto'
                    });
                }
            }
        }
        fix();
        $(window).scroll(fix);
      }
      //个人中心滚动菜单固定
      $('#block-sbq-commons-sbq-user-menu').fixedDiv('fixed')
    }


    $('.views-field-field-tags-disease li').live('hover', function(){
        $(this).children('span').toggleClass('show');
        $(this).children('a').toggleClass('hover');

    })

    /*个人中心添加标签*/
    $('#sbq-user-disease-add').focus(function() {
      var tval = $.trim($(this).val());
      if(tval == '回车添加标签'){
        $(this).val('');
      }
    });
    $('#sbq-user-disease-add').blur(function() {
      var tbval = $.trim($(this).val());
      if(tbval == ''){
        $(this).val('回车添加标签');
      }
    });

    $('#sbq_doctor_quick_register button.close').live('click',function(){
    	$('#sbq_doctor_quick_register').hide();
    })
    /*我的帖子*/
    $('#block-sbq-commons-sbq-user-menu .sbq-user-menu-post a').click(function() {
      var ttop = $('#block-quicktabs-user-group').offset().top-30;
      $('html,body').animate({ scrollTop: ttop }, 1000);
      return false;
    });
    /*我的动态*/
    $('#block-sbq-commons-sbq-user-menu .sbq-user-menu-status a').click(function() {
      var btop = $('#block-quicktabs-message').offset().top-30;
      $('html,body').animate({ scrollTop: btop }, 1000);
      return false;
    });
    /*我的文章*/
    $('#block-sbq-commons-sbq-user-menu .sbq-user-menu-blog a').click(function() {
      var btop = $('#block-views-blog-my-blog-block').offset().top-30;
      $('html,body').animate({ scrollTop: btop }, 1000);
      return false;
    });
    $('.view-og-user-groups .views-row,.view-og-extras-groups .views-row').hover(function(){
      $(this).children('.views-field-body').show();
    },function(){
      $(this).children('.views-field-body').hide();
    })

    /*个人中心提交问题*/
    $('#block-sbq-commons-sbq-quick-ask #edit-submit--2').click(function() {
      /* Act on the event */
      var qs = $.trim($('#edit-body-und-0-value').val());
      if(qs){
        var today = new Date();
        var todayString = today.getFullYear() +'-'+today.getMonth() + '-' + today.getDate();
        var nqs  = '<div class="views-row views-row-1 views-row-odd views-row-first">';
            nqs += '<div class="views-field views-field-title"><span class="field-content">'+qs+'</span>  </div>';
            nqs += '  <div class="views-field views-field-value">        <span class="field-content">0</span>  </div> ';
            nqs += '  <div class="views-field views-field-field-mark-question-resolved">        <div class="field-content">未解决</div>  </div>  ';
            nqs += '  <div class="views-field views-field-created">        <span class="field-content">'+todayString+'</span>  </div>  </div>';

        $('#quicktabs-tabpage-user_qa-0 .view-content').prepend(nqs)
      }
      return false;
    });
    //评测视频切换
    $('.sbq_field_title_list .field-item a').click(function() {
      var tidx = $(this).parents('.field-item').index();
      $(this).parents('.field-items').find('a.active').removeClass('active');
      $(this).addClass('active').parents('.sbq_field_title_list').prev('.sbq-field-video-list').find('.field-items').children('.field-item').eq(tidx).show().siblings().hide();
      return false;
    });
    $('#node_wiki_full_group_tech h2').click(function() {
      var thidx = $(this).index();
      $(this).addClass('active').siblings('h2').removeClass('active');
      $(this).parents('#node_wiki_full_group_tech').children('.view-wiki').eq(thidx).show().siblings('.view-wiki').hide();
    });
    $('#node_wiki_child_full_group_content .field-label').click(function() {
      var tdidx = $(this).index();
      if($('.sbq-field_video_warpper').is('.active')){
        $(this).parent().removeClass('n');
        $('.sbq-field_video_warpper').removeClass('active').siblings('.field-type-text-with-summary').addClass('active')
      }else{
        $(this).parent().addClass('n');
        $('.field-type-text-with-summary').removeClass('active').siblings('.sbq-field_video_warpper').addClass('active')
      }
      $(this).parents('#node_wiki_child_full_group_content').children('.wiki-field').eq(tdidx).show().siblings('.wiki-field').hide();
    });
  }


};


})(jQuery, Drupal, this, this.document);
