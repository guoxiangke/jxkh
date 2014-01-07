jQuery(function($) {
  $("a.log").colorbox({
    innerWidth : "500px",
    height : "320px",
    onClosed : function(){
      location.reload(true);
    }
  });
});
