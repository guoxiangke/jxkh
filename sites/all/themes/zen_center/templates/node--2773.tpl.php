<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
    <header>
      <?php print render($title_prefix); ?>
      <?php if (!$page && $title): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
        <p class="submitted">
          <?php print $user_picture; ?>
          <?php print $submitted; ?>
        </p>
      <?php endif; ?>

      <?php if ($unpublished): ?>
        <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print render($content);
  ?>
<!---->
<div id="node_wiki_full_group_tech" class="group-tech field-group-div">
  <h3>
    <span>科学</span>
  </h3>
  <div class="sbq-group-tech-tab">
    <h2 class="title active">科学</h2>
    <h2 class="title">科学实验报告</h2>
  </div>
  <div class="view view-wiki view-id-wiki view-display-id-wiki_tech_eva view-dom-id-b5e95f154072393d8913ca276e10fbe9 contextual-links-region">
    <div class="view-content">
      <div class="views-row views-row-1 views-row-odd views-row-first views-row-last">
        <a href="/node/2771">#1科学知识for血糖仪 </a>    2013-10-10 10:06
      </div>
    </div>
  </div>
  <div class="view view-wiki view-id-wiki view-display-id-report_eva view-dom-id-fa57c1304439df5c2f5cdb57be20dea1 contextual-links-region">
    <div class="view-content">
      <div class="views-row views-row-1 views-row-odd views-row-first">
        <a href="/node/2774">血糖仪报告#1</a>    2013-10-10 11:54
      </div>
      <div class="views-row views-row-2 views-row-even views-row-last">
        <a href="/node/2793">血糖仪与实验室检测血糖比对分析报告#2</a>    2013-10-15 17:34
      </div>
    </div>
  </div>
</div>
<!---->
  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
