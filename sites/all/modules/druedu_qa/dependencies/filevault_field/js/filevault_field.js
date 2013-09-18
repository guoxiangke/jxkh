
(function ($) {

  Drupal.filevault_field = Drupal.filevault_field || {};

    Drupal.behaviors.filevault_field = {

      attach: function (context, settings) {
        // Set the initial state of the field.
        $('#edit-field-filevault', context).once('setup_field', function(){
            Drupal.filevault_field.init();
        });

        // When adding new field
        //$('#edit-field-filevault', context).change(function () {
        //});

      }
  };

  // Setup event listeners
  Drupal.filevault_field.init = function() {

    // Is the filevault block activated
    if( !$('#filevault_ui_block').length >= 1 ){
      // No.. better notify the admin
      return;
    }

    $('#filevault_ui_block ul.files a').live('click', function (e){
      e.preventDefault();

      var json = $(this).parents('li').data('json');

      // Find an empty input field and input the id of filevault file
      $('input.filevault_id').each(function(index, element) {
        if( $(element).val() == "" ){
          $(element).val(json.id);
          $(element).parents('td').find('.filevault_vid').val('0');
          return false;
        }
      });

    });

  }

  Drupal.filevault_field.addnew = function() {


  }

})(jQuery);
