(function ($) {
  Drupal.behaviors.sbq_center = {
    attach: function (context, settings) {
      // js here
      $('.sbq-message').delay(3000).fadeOut();

      var bannerBackground = $('#sbq-banner img').attr('src');
      $('#sbq-banner').css('background-image', 'url("' + bannerBackground + '")');
      $('#sbq-banner').css('background-position', 'center');
      // js end
    }
  };
})(jQuery);