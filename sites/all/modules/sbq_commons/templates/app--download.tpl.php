<div class="sbq_apps">
  <div class="sbq_apps_top">
    <div class="image">
      <image src="/<?php print path_to_theme() ?>/images/blj_logo.png">
    </div>
    <div class="down">
      <h2>病历本 - 治疗从记录开始，让病历记录更简单！</h2>
      <?php
      foreach (
      array( 'apple' => '点击下载iphone版', 'quick' => '快用下载iphone版病例夹',
          'android' => '点击下载安卓版', 'sbq_web' => '病例夹网站版' ) as $key => $item):
        ?>
        <a href="" class="<?php print $key ?>_href">
          <i class="<?php print $key ?>">
            <image src="/<?php print path_to_theme() ?>/images/<?php print $key ?>.gif">
          </i> 
          <?php print $item ?>
        </a>
      <?php endforeach; ?>
    </div>
  </div>
  <div class="project">
    <div class="info">
      <h3>产品介绍</h3>
      <p>★定位：第一个为患者定制的移动病历记录云服务工具</p>
      <p>病历本——您手机里的病历小本，帮助患者在日常生活中，用智能手机快速方便地记录、管理和查找病历资料，为患者建立一个安全存储病历资料的云空间。</p>
      <dl>
        <dt>病历本能帮我做什么</dt>
        <dd>随时，随地，快速用手机记录（自己或家人）病历资料。</dd>
        <dd>随时，随地，快速用手机记录（自己或家人）病历资料自己的病情记录、影像资料、个人分析，所有信息统统放在一起，再也不用担心记不清自己的发病经历。</dd>
        <dd>就诊时，你的主治医生可以清晰了解你的发病程，不用再担心没和医生表述遗漏重要信息，便捷查询、编辑以前保存的病历。</dd>
        <dd>重要事情提醒功能，提高患者的依从性。</dd>
        <dd>资料同步云端，实时多重备份，永不丢失。</dd>
        <dd>免费使用，免费云端空间，无限量增长。</dd>
      </dl>
    </div>

    <div class="special">
      <h3>产品特性</h3>
      <dl>
        <dt>病历本能帮我做什么</dt>
        <dd>- 简洁清新的用户界面，专为患者记录病历使用。</dd>
        <dd>- 联网或不联网时都可以使用。</dd>
        <dd>- 通过拍照、录音等功能，快速记录病历资料和个人说明。</dd>
        <dd>- 内置疾病专业数据库，管理小工具，方便快速记录。</dd>
        <dd>- 照片、录音强力高保真压缩，节约手机空间，同步更迅速。</dd>
        <dd>- 所有云端病历资料实时多重备份，安全稳定有保障，永不丢失泄露。</dd>
      </dl>
    </div>

    <div class="special">
      <h3>产品界面</h3>
      <div id="carousel-example-generic" class="carousel slide" data-ride="carousel">
        <!-- Indicators -->
        <!--        <ol class="carousel-indicators">
                  <li data-target="#carousel-example-generic" data-slide-to="0" class="active">
                  
                  </li>
                  <li data-target="#carousel-example-generic" data-slide-to="1">
                    
                  </li>
                  <li data-target="#carousel-example-generic" data-slide-to="2">
                   
                  </li>
                </ol>-->

        <!-- Wrapper for slides -->
        <div class="carousel-inner">
          <?php for ($i = 1; $i <= 6; $i++): ?>
            <div class="item <?php echo $i <= 3 ? 'active' : ''; ?>" style="float:left; margin-left: 10px;">
              <image src="/<?php print path_to_theme() ?>/images/blj/blb<?php print $i ?>.jpg">
              <div class="carousel-caption">

              </div>
            </div>
          <?php endfor; ?>

        </div>

        <!-- Controls -->
        <a class="left carousel-control" href="#carousel-example-generic" data-slide="prev">
          <span class="glyphicon glyphicon-chevron-left">
            <image src='/<?php print path_to_theme() ?>/images/prev-horizontal.gif'>
          </span>
        </a>
        <a class="right carousel-control" href="#carousel-example-generic" data-slide="next">
          <span class="glyphicon glyphicon-chevron-right">
             <image src='/<?php print path_to_theme() ?>/images/next-horizontal.gif'>
          </span>
        </a>
      </div>
    </div>
  </div>
</div>