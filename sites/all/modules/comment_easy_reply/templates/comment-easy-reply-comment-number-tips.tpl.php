<?php

/**
 * @file
 * Theme implementation for comment number link tooltip.
 *
 * Available variables:
 * - $tips: The text that will appear inside the tooltip.
 *
 * These variables are provided for context:
 * - $comment: Full comment object.
 * - $comment_num: Comment number.
 *
 *
 * @see template_preprocess_comment_easy_reply_comment_number_tips()
 */
?>
<span class="comment-easy-reply-number-link-tips comment-easy-reply-number-link-tips-<?php print $comment_num;?>" style="display:none;">
<?php print $tips; ?>
</span>
