package fr.louino.lcdlink;

import org.bukkit.plugin.java.JavaPlugin;
import org.bukkit.scheduler.BukkitRunnable;

import net.minecraft.server.v1_16_R2.MinecraftServer;


public class main extends JavaPlugin {
	
	@Override
	public void onEnable() {
		saveDefaultConfig();
		getConfig().set("online", 1);
		getConfig().set("players", getServer().getOnlinePlayers().size());
		getConfig().set("maxplayers", getServer().getMaxPlayers());
		saveConfig();
		getServer().getPluginManager().registerEvents(new PluginListeners(this), this);
		new BukkitRunnable() {
			@Override
			public void run() {
				@SuppressWarnings({ "resource", "deprecation" })
				double[] tps = MinecraftServer.getServer().recentTps;
				globalvars.activetps = (float) (Math.round(tps[0]* 100.0)/100.0);
				if (globalvars.activetps > 20) {
					globalvars.activetps = 20;
				}
				if (globalvars.oldtps != globalvars.activetps) {
					globalvars.oldtps = globalvars.activetps;
					getConfig().set("tps", globalvars.activetps);
					saveConfig();
				}
				
				
				globalvars.activeplayers = getServer().getOnlinePlayers().size();
				if (globalvars.oldplayers != globalvars.activeplayers) {
					globalvars.oldplayers = globalvars.activeplayers;
					getConfig().set("players", Math.round(globalvars.activeplayers));
					saveConfig();
					
				}
				
			}
		}.runTaskTimer(this, 0, 20);
		
	}
	
	@Override
	public void onDisable() {
		getConfig().set("online", 0);
		getConfig().set("players", 0);
		saveConfig();
	}
	
}
