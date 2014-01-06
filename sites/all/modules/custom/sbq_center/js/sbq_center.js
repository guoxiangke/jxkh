(function ($) {
  Drupal.behaviors.sbq_center = {
    attach: function (context, settings) {
      // js here
      $('.sbq-message').delay(3000).fadeOut();

      // js end
    }
  };
})(jQuery);