jQuery(function($) {
	$('.alert-block a.close').click(function(){
		$(this).parents('.alert-block').hide();
	});		
	$('.node-type-sbq-topic textarea').focus(function(){
			$(this).attr('value','');
	});
        $('.user_doctor_register_ajax').click(function(){
          $.get('/doctor/register', function(data){
           $(data).modal()
          })//.success(function() { $('input:text:visible:first').focus(); });
          return false;
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
