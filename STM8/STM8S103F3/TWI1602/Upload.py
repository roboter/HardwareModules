Import("env")
import subprocess

# set upload command
def before_upload(source, target, env):
  cmd = 'STVP_CmdLine -BoardName=ST-LINK -ProgMode=SWIM -Tool_ID=0 -Device=STM8S103F3 -no_loop -FileProg=.pio\\build\\stm8sblue\\firmware.ihx'
  subprocess.Popen(cmd)

# call upload coammand
env.AddPreAction("upload", before_upload)

