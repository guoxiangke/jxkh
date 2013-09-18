<div class="modal hide fade large" id="filevault-modal" role="dialog" aria-labelledby="filevaultLabel" aria-hidden="true">

  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
    <h3 id="filevaultLabel">FileVault</h3>
  </div>

  <div class="modal-body">
      <div class="row-fluid">
        <ul class="thumbnails"></ul>
      </div><!-- row-fluid -->
  </div><!-- modal-body -->
  <script id="filevault_modal_template_image" type="text/x-dot-template">
    <li class="span2 image file">
      <div class="thumbnail">
        <img src="{{=it.thumbnail}}" data-embedded="{{=it.thumbnail}}" data-original="{{=it.original}}" style="float:left; margin:10px;">
        <div class="caption">
          <p class="filename">{{=it.filename}}</p>
          <p><a href="#" class="btn btn-primary">Insert</a></p>
        </div>
      </div>
    </li>
  </script>

  <script id="filevault_modal_template_video" type="text/x-dot-template">
    <li class="span2 video file">
      <div class="thumbnail">
        <video width="320" height="240" controls="controls" poster="{{=it.thumbnail}}" preload="metadata" style="float:left; margin:10px;">
          <source src="{{=it.original}}" type="{{=it.minetype}">
          Your browser does not support the video tag.
        </video>
        <div class="caption">
          <p class="filename">{{=it.filename}}</p>
          <p><a href="#" class="btn btn-primary">Insert</a></p>
        </div>
      </div>
    </li>
  </script>

  <script id="filevault_modal_template_document" type="text/x-dot-template">
    <li class="span2 document file">
      <div class="thumbnail">
        <img src="{{=it.thumbnail}}">
        <div class="caption">
          <p class="filename">{{=it.filename}}</p>
          <p><a href="#" class="btn btn-primary">Insert</a></p>
        </div>
      </div>
    </li>
  </script>

</div><!-- filevault-modal -->
