/**
 * Created by chaser on 2/24/14.
 */
function deleteVote(id) {
  alert(id);
  jQuery("#newRuleList > li").each(function (n, item) {
    if (item.id == id) {
      //jQuery(item).effect("fade", {}, 500, function(){
      //    jQuery(item).remove();
      //});
      jQuery(item).hide(500, function () {
        jQuery(item).remove();
      });
    }
  });
}