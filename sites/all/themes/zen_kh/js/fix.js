jQuery(function($) {
	//fix
	$("#user-login-form .captcha img").appendTo('#user-login-form .captcha .form-item-captcha-response');
	$("#user-login-form .captcha img").click(function() {
		$("#user-login-form .captcha .reload-captcha").click();
	});
	$("#user-login-form #edit-captcha-response").attr("placeholder", "验证码");
});

