jQuery(function($) {
	//index
	$(".captcha img").appendTo('.captcha .form-item-captcha-response');
	$(".captcha img").click(function() {
		$(".captcha .reload-captcha").click();
	});
	$("#user-login-form #edit-captcha-response").attr("placeholder", "验证码");
	//reg

	//$(".user-info-from-cookie .captcha .reload-captcha").click();
	//END
});

