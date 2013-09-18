<section id="filevault_core_block" class="block">

  <?php print render($filevault_form); ?>

  <script id="filevault_core_template_image" type="text/x-dot-template">
        <img src="{{=it.embedded}}" data-original="{{=it.url}}" style:"float:left; margin:10px;">
  </script>

  <script id="filevault_core_template_video" type="text/x-dot-template">
        <video width="320" height="240" controls="controls" poster="{{=it.thumbnail}}" preload="metadata" style:"float:left; margin:10px;">
          <source src="{{=it.original}}" type="{{=it.minetype}">
          Your browser does not support the video tag.
        </video>
  </script>

  <script id="filevault_core_template_document" type="text/x-dot-template">
        <img src="{{=it.thumbnail}}" style:"float:left; margin:10px;">
  </script>

</section>

