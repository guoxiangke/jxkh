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
    $.getScript('http://dev.shangbq.com/sites/all/themes/zen_kh/js/Carousel.js',function(){
      $('#myCarousel').carousel({
  		  interval: 4000
  		})
      $('#sbq-user-carousel').carousel({
        interval: 5000
      })
    })
    $('.views-field-field-tags-disease li').hover(function(){
        $(this).children('span').toggleClass('show');
        $(this).children('a').toggleClass('hover');

      })
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
    $('.view-og-user-groups .views-row,.view-og-extras-groups .views-row').hover(function(){
      $(this).children('.views-field-body').show();
    },function(){
      $(this).children('.views-field-body').hide();
    })

    /*个人中心提交问题*/
    $('#edit-submit--2').click(function(event) {
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
  }
};


})(jQuery, Drupal, this, this.document);
