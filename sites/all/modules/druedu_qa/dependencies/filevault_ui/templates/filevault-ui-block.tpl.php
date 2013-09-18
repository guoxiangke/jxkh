<section id="filevault_ui_block" class="block">

  <div class="progress_bars">

    <div class="progress" id="progress_all">
      <div class="bar" style="width: 75%;"></div>
    </div>

    <div class="progress" id="progress_single">
      <div class="bar" style="width: 47%;"></div>
    </div>

  </div>

  <div class="dropzone">
    <p>Drag'n'drop to upload files <br /> or click here</p>
  </div>

  <div class="filelist">
    <button class="btn btn-mini disabled" type="button" id="prev">Prev</button>
    <button class="btn btn-mini" type="button" id="next">Next</button>

    <ul></ul>
  </div>

  <script id="filevault_block_template_image" type="text/x-dot-template">
      <li class="image">
        <img src="{{=it.thumbnail}}" height="100px" style="float:left; margin:10px;"/>
        <span class="filename">{{=it.filename}}</span>
      </li>
  </script>

  <script id="filevault_block_template_video" type="text/x-dot-template">
      <li class="video">
        <video height="100" controls="controls" style="float:left; margin:10px;">
          <source src="{{=it.original}}" type="video/mp4">
            Your browser does not support the video tag.
        </video>
        <span class="filename">{{=it.filename}}</span>
      </li>
  </script>

  <script id="filevault_block_template_document" type="text/x-dot-template">
      <li class="document">
        <a href="{{=it.original}}"> <img src="TBD" height="100" /></a>
        <span class="filename">{{=it.filename}}</span>
      </li>
  </script>

</section>
