jQuery(function($) {
  // $("a.log").colorbox({
  //   innerWidth : "500px",
  //   height : "370px",
  //   onClosed : function(){
  //     location.reload(true);
  //   }
  // });

  //textarea focus
  $(".sbq_quick_question textarea").focus(function() {
    $(this).parent().addClass('on');
  });
  $(".sbq_quick_question textarea").blur(function() {
    $(this).parent().removeClass('on');
  });

});
