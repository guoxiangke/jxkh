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
		  interval: 3000
		})
    })
  }
};


})(jQuery, Drupal, this, this.document);
