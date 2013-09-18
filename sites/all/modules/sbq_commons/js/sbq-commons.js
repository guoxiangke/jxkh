jQuery(function($) {
	$('.alert-block a.close').click(function(){
		$(this).parents('.alert-block').hide();
	});
	Drupal.behaviors.druedu_qa = {
     attach: function (context, settings) {
				$('.alert-block a.close').click(function(){
					$(this).parents('.alert-block').hide();
				});
		}
	}
});
