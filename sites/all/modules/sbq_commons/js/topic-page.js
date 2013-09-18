jQuery(function($) {
	$('.sbq-center-box .comment-form').hide();
	var arrow_speed = 300;
		$('#technology-arrow').on({
			mouseenter: function() {
				$(this).animate( { 'left' : '30px' }, arrow_speed);
			},
			mouseleave: function() {
				$(this).stop(true,true).animate( { 'left' : '60px' }, arrow_speed);
			}	
		});
		
		$('#team-arrow').on({
			mouseenter: function() {
				$(this).animate( { 'right' : '90px' }, arrow_speed);
			},
			mouseleave: function() {
				$(this).stop(true,true).animate( { 'right' : '130px' }, arrow_speed);
			}	
		});
		
		

		$('#technology-arrow').click(function(){
			$(".node-sbq-topic .rate-widget-yesno a[title='支持']").click();
			$('.form-item-field-field-sbq-topic-type-und  input[type="checkbox"]').attr("checked","checked");
		});
		$('#team-arrow').click(function(){
			$(".node-sbq-topic .rate-widget-yesno a[title='反对']").click();
			$('.form-item-field-field-sbq-topic-type-und input[type="checkbox"]').attr("checked",false);
		});

		$('.sbq_topic_positive').click(function(){
			$(this).attr('class','sbq_topic_positivenone');
			// val = $('.sbq_topic_positive_statics_right').attr('data-total')/$('.sbq_topic_positive_statics_right').attr('data-total')+1;
			$(this).css("height", '100%');
		})
		$('.sbq_topic_negative').click(function(){
			$(this).attr('class','sbq_topic_negativenone');

			$('.sbq_topic_positive_statics_right').css("height", '100%');

		})
		
		$('textarea').focus(function(){
			$(this).attr('value','');
		});

	Drupal.behaviors.druedu_qa = {
     attach: function (context, settings) {
			ToggleSlideTopic(context);
		}
	}

function ToggleSlideTopic(context) {
	$('a.sbv-show-cform', context).click(function(e) {
		e.preventDefault();
		$(this).parents('.views-row').children('.comment-form').slideToggle('1000');
	});
}

	ToggleSlideTopic();
});
