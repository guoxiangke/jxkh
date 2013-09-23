jQuery(function($) {
	ToggleSlide('');
	function CKupdate() {
		if( typeof CKEDITOR != 'undefined')
		for ( instance in CKEDITOR.instances ) {
			// CKEDITOR.instances[instance].updateElement();
			CKEDITOR.instances[instance].setData('');
		}
	}
// 	$('#answer-node-form button[type="submit"]').attr('disabled', 'disabled');

//  	//Upload a file or insert on ckeditor enabled submit button
//  	$('#files_uploaded_container .insert').live('click',function(){ 
//        	$('#answer-node-form button[type="submit"]').removeAttr('disabled');
//     });

//    	$('#filevault_core_block').bind('fileuploaddone', function() {
//         	$('#answer-node-form button[type="submit"]').removeAttr('disabled');
//     });
	// for ( instance in CKEDITOR.instances )
	// 	CKEDITOR.instances[instance].on( 'blur', function( e ){
	// 	  CKcheck(CKEDITOR.instances[instance]);
	// 	});
	// $('#edit-field-attachments').hover(function(e){
	// 	for ( instance in CKEDITOR.instances )
	// 		CKcheck(CKEDITOR.instances[instance]);
	// });

	// $('#answer-node-form button[type="submit"]').hover(function(e){
	// 		for ( instance in CKEDITOR.instances )
	// 		CKcheck(CKEDITOR.instances[instance]);
	// });

	// var checked = false;
	// // console.log($('#answer-node-form button[type="submit"]'));
	// $('#answer-node-form button[type="submit"]').click(function(e){
	// 	console.log('cli');
	// 	if(!checked){
	// 		e.preventDefault();
	// 		for ( instance in CKEDITOR.instances )
	// 			if(CKcheck(CKEDITOR.instances[instance])){
	// 				checked = true;
	// 				$(this).click();
	// 			}
	// 	}
	// });

	Drupal.behaviors.druedu_qa = {
     attach: function (context, settings) {
			// $('.comments-wrapper .has-comment').after('<b class="triangle_top"></b>');
			ToggleSlide(context);
			CKupdate();//Always ckeditor not $('#edit-body-und-0-value').val(' ');
			// $('#answer-node-form textarea').attr('value', '');
			var checked = false;
			// for ( instance in CKEDITOR.instances )
			// 	 CKcheck(CKEDITOR.instances[instance]);
		}
	}

	$.fn.insertComment = function(args) {
		$(args.selector).append(args.data);
	};

	$.fn.disableSubmitButton = function() {
		// $('#answer-node-form button[type="submit"]').attr('disabled', 'disabled');
		$('#files_uploaded_container .remove_file').each(function(){
			$(this).click();
		});
		$('#files_uploaded').attr('class','hide');
	};



function ToggleSlide(context) {
	//$('.fed_button').popover();

	$('.comment_button', context).click(function(){
		$(this).parents('.comments_answer').children('.comment_textarea').slideToggle('1000');
		$(this).parents('.comments_question').children('.comment_textarea').slideToggle('1000');
	});

	$('.comment_textarea a', context).click(function(e){
		e.preventDefault();
		$(this).parent().hide();
	});


	// $('.fed_button', context).click(function(){
	// 	$('.feedback-wrapper').show();
	// });

	// Change the color of vote number when can not vote
	$('span.rate-button').next('.rate-number-up-down-rating').css('color',"#919191");

	$('.rate-widget-yesno').hover(function(){
		$('.qa-userful-buttons').show();
	} ,function(){
		$('.qa-userful-buttons').hide();
	});
}

});
