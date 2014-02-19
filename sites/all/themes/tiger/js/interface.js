jQuery(function($) {
	//login light BOX
	/*$("a.log").colorbox({
	innerWidth : "500px",
	height : "320px"
	});*/
	//USER textarea focus
	$(".sbq_quick_question textarea").focus(function() {
		$(this).parent().addClass('on');
	});
	$(".sbq_quick_question textarea").blur(function() {
		$(this).parent().removeClass('on');
	});
	//USER sbq_user_menu
	$(".sbq_user_menu .sbq_more_list").hover(function() {
		$(this).find('span').show();
		$(this).addClass('on');
	}, function() {
		$(this).find('span').hide();
		$(this).removeClass('on');
	});
	//ALL go to top
	$(".header").append('<a href="#" id="sbq_gototop"></a>');
	$(function() {
		//F5
		if ($(window).scrollTop() > 100) {
			$("#sbq_gototop").show();
		} else {
			$("#sbq_gototop").hide();
		}
		//scroll show hide
		$(window).scroll(function() {
			if ($(window).scrollTop() > 100) {
				$("#sbq_gototop").fadeIn(100);
			} else {
				$("#sbq_gototop").fadeOut(50);
			}
		});
		//btn
		$("#sbq_gototop").click(function() {
			$('body,html').animate({
				scrollTop : 0
			}, 500);
			return false;
		});
	});
	//ALL close
	$(".sbq_messages .messages").append('<span id="sbq_close">关闭</span>');
	$(".sbq_messages #sbq_close").click(function() {
		$(this).parents(".messages").fadeOut(500);
	});
	//test
	//$(".header_inner").append('<div class="sbq_search_form"><input type="text" class="sbq_search_form_text" placeholder="请输入搜索关键字"><input type="submit" value="搜索" class="sbq_search_form_btn"></div>');
});
