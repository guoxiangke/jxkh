jQuery(function($) {
  $('.alert-block a.close').click(function(){
    $(this).parents('.alert-block').hide();
  });		
  $('.node-type-sbq-topic textarea').focus(function(){
    $(this).attr('value','');
  });
  $('.user_doctor_register_ajax').click(function(){
    var href = $(this).attr('href');
    if( $('#sbq_doctor_quick_register').length > 0){
      $('#sbq_doctor_quick_register').modal();
    }else{
      var self = $(this);
      self.parent().parent().find("li.first").append('<div id="status" style="background: url(/misc/throbber.gif) no-repeat 5px -16px; width:21px; height:16px;display: inline-block;"> </div>');
      $.get(href+'?ajax=true', function(data){ 
        self.parent().parent().find("li #status").remove()
        $(data).modal();
      });
    }
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
