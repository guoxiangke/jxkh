jQuery(function($) {
  var currentUrl = Drupal.settings.current_url;
  prepareAjaxRefresh();
  if(typeof getStatutFilevaultField == 'function') { 
    filevaultFieldEnabled = getStatutFilevaultField(); 
  }
  var Json = Drupal.settings.json;
  prepareJson(Json);

  $('body').bind('ajaxSuccess', function(data, status, xhr){
    if(xhr.url.indexOf('views/ajax')) { 
      var Json = Drupal.settings.json;
      prepareJson(Json);
      prepareAjaxRefresh();
    }
  });

  //refresh modal view after upload a new file
  $('#filevault_core_block').bind('fv_upload_done fileuploaddone', function(e, data) {
    $('.modal-refresh').click();
    //by simulate a click on filter : $('#edit-submit-filevault-modal').click();
    //by simulate a click on pager : $('.view-id-filevault_modal.view-display-id-filevault_modal_block ul.pager li.active a').click();
  });

  function prepareAjaxRefresh() {
    $.each(Drupal.views.instances, function(index, obj) {
      if(obj.settings.view_display_id == "filevault_modal_block") {
        var $link = $('.modal-refresh');
        var viewData = {};
        var href = currentUrl;
        // Construct an object using the settings defaults and then overriding
        // with data specific to the link.
        $.extend(
          viewData,
          obj.settings,
          Drupal.Views.parseQueryString(href),
          // Extract argument data from the URL.
          Drupal.Views.parseViewArgs(href, obj.settings.view_base_path)
        );
        // For anchor tags, these will go to the target of the anchor rather
        // than the usual location.
        //$.extend(viewData, Drupal.Views.parseViewArgs(href, obj.settings.view_base_path));
        obj.element_settings.submit = viewData;
        if(typeof Drupal.ajax['modal-refresh'] == 'undefined') {
          Drupal.ajax['modal-refresh'] = new Drupal.ajax(false, $link, obj.element_settings);
        }
        else{
          Drupal.ajax['modal-refresh'].element_settings = obj.element_settings;
        }
        return false;
      }
     });
  }
  function prepareJson(Json) {
    if(filevaultFieldEnabled && typeof Json != 'undefined') {
      $.each(Json, function(index, value) {
        var key = index+1;
        $('.modal-files li:nth-child('+key+')').data('json', jQuery.parseJSON(value));
      });
    }
  };
  var fileindex = 0;
/*
  jQuery.getJSON(Drupal.settings.basePath+"/filevault/block/list/0/"+fileindex+10, function(json) {

    //var imageTemplate = doT.template(document.getElementById('filevault_modal_template_image').text, undefined, undefined);
    //var videoTemplate = doT.template(document.getElementById('filevault_modal_template_video').text, undefined, undefined);
    //var documentTemplate = doT.template(document.getElementById('filevault_modal_template_document').text, undefined, undefined);

    fileindex += json.length;
    for (var i=0;i<json.length;i++){

      $('.widget').find('.delete').click(function(e) {
            $(this).parent().remove();
      });

      if(json[i].mime_type.indexOf("image") != -1){
        var element = jQuery(imageTemplate(json[i])).data('json',json[i]);
        jQuery('#filevault-modal .modal-files').append(element);
        continue;
      }

      if(json[i].mime_type.indexOf("mp4") != -1){
        var element = jQuery(videoTemplate(json[i])).data('json',json[i]);
        jQuery('#filevault-modal .modal-files').append(element);
        continue;
      }
      var element = jQuery(documentTemplate(json[i])).data('json',json[i]);
      jQuery('#filevault-modal .modal-files').append(element);
    }

  });
*/
  jQuery('#filevault-modal .insert').live("click", function (e){
    if(!filevaultFieldEnabled) {
      Drupal.insert.insertIntoActiveEditor( jQuery(this).parents('li').find('.payload').html() );
      $("#filevault-modal").modal("hide");
    }
      //if( typeof interactive_editor_enabled !== "undefined"  ){
      //  if(interactive_editor_enabled){
      //    Drupal.insert.insertIntoActiveEditor( jQuery(this).parents('li').find('.payload').html() );
      //    $("#filevault-modal").modal("hide");
      //  }
      //}
  });

/*

  jQuery('#filevault_block button.next').click(function(e) {

    jQuery.getJSON(Drupal.settings.basePath+"/filevault/block/list/" + fileindex, function(json) {

      if(json.length > 0){
        fileindex += json.length;
        jQuery('#filevault_block #filelist').html('');
        for (var i=0;i<json.length;i++){
          jQuery('#filevault_block #filelist').append( imageTemplate(json[i]) );
        }
      }

    });

  });

  jQuery('#filevault_block button.prev').click(function(e) {

    if(fileindex == 0){
      return;
    }

    fileindex -= 8;
    if( fileindex < 0){
      fileindex = 0;
    }

    jQuery.getJSON(Drupal.settings.basePath+"/filevault/block/list/" + fileindex, function(json) {
      jQuery('#filevault_block #filelist').html('');
      for (var i=0;i<json.length;i++){
        jQuery('#filevault_block #filelist').append( imageTemplate(json[i]) );
      }
    });

  });
 */
});
