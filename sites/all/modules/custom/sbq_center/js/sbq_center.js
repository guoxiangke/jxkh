(function ($) {
  Drupal.behaviors.sbq_center = {
    attach: function (context, settings) {
      $('.sbq-message').delay(3000).fadeOut();
    }
  };
})(jQuery);