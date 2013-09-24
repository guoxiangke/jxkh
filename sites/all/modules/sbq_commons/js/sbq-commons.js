jQuery(function($) {
	$('.alert-block a.close').click(function(){
		$(this).parents('.alert-block').hide();
	});		
	$('.node-type-sbq-topic textarea').focus(function(){
			$(this).attr('value','');
	});
	Drupal.behaviors.sbq_commons = {
     attach: function (context, settings) {
				$('.alert-block a.close').click(function(){
					$(this).parents('.alert-block').hide();
				});
				
				$('.node-type-sbq-topic textarea').focus(function(){
						$(this).attr('value','');
				});
		}
	}
});
