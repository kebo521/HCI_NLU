logset(0);
loadlib"dll/ui.dll";
loadlib"dll/uart.dll";
loadlib"dll/tts.dll";
loadlib"dll/crypt.dll";
def ollamapath(tag)
{
	dd=inf(getenv("OLLAMA_MODELS")+"\\manifests\\registry.ollama.ai\\library\\"+replace(tag,":","\\"));
	if(!dd) return false;
	fd=jsonload(dd);
	if(!fd) return false;
	val=jsongey(fd,"layers[0].digest");
	jsonfree(fd);
	if(!val) return false;
	return (getenv("OLLAMA_MODELS")+"\\blobs\\"+replace(val,":","-"));
}