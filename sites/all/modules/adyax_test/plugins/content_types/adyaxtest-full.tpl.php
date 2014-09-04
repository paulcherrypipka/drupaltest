<style>
  <?php //print 'div.pane-adyaxtest {border: ' . $border_style . 'px solid gray!important; border-radius: 10px!important;}'; ?>
</style>
<?php foreach($nodes as $node): ?>
  <div class="adyaxtest">
    <?php print $node; ?>
  </div>
<?php endforeach; ?>
