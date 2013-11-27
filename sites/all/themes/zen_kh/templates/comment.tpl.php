<?php
/**
 * @file
 * Returns the HTML for comments.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728216
 */
?>
<article class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print $picture; ?>
  <header>
    <div class="submitted">
      <?php print $submitted; ?>
      <?php 
      global $user;
      if($user->uid)    {
  print render($content['links']); 
  }else {
    // echo '<div style="width:100px;height:100px;background:#666;"';
    echo '<ul class="links inline">
            <li class="comment-reply first last">
              <a href="/user/login" class="use-ajax ajax-processed">登录后发表评论</a>
            </li>
          </ul>';
  }


  ?>
      <?php // print $permalink; ?>
    </div>

    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
<?php /*
      <h3<?php print $title_attributes; ?>>
        <?php print $title; ?>
        <?php if ($new): ?>
          <mark class="new"><?php print $new; ?></mark>
        <?php endif; ?>
      </h3>
      */
?>
    <?php elseif ($new): ?>
      <mark class="new"><?php print $new; ?></mark>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php if ($status == 'comment-unpublished'): ?>
      <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
    <?php endif; ?>
    <?php
     // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?>
  </header>



  <?php if ($signature): ?>
    <footer class="user-signature clearfix">
      <?php print $signature; ?>
    </footer>
  <?php endif; ?>

  
</article>