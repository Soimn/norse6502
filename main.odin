package main

import "core:slice"
import "core:fmt"
import "core:strings"
import "core:strconv"

import "netlist_sim"

foreign import assembler "./build/assembler.obj"
foreign assembler
{
	@(link_name = "ParseProgram") ParseProgram :: proc(filename: cstring, program_memory: ^u8) -> bool ---;
}

DisassemblyTable := []string{
	0x00 = "BRK",
	0x01 = "ORA (zp,X)",
	0x05 = "ORA zp",
	0x06 = "ASL zp",
	0x08 = "PHP",
	0x09 = "ORA #",
	0x0A = "ASL",
	0x0D = "ORA Abs",
	0x0E = "ASL Abs",
	0x10 = "BPL",
	0x11 = "ORA (zp),Y",
	0x15 = "ORA zp,X",
	0x16 = "ASL zp,X",
	0x18 = "CLC",
	0x19 = "ORA Abs,Y",
	0x1D = "ORA Abs,X",
	0x1E = "ASL Abs,X",
	0x20 = "JSR Abs",
	0x21 = "AND (zp,X)",
	0x24 = "BIT zp",
	0x25 = "AND zp",
	0x26 = "ROL zp",
	0x28 = "PLP",
	0x29 = "AND #",
	0x2A = "ROL",
	0x2C = "BIT Abs",
	0x2D = "AND Abs",
	0x2E = "ROL Abs",
	0x30 = "BMI",
	0x31 = "AND (zp),Y",
	0x35 = "AND zp,X",
	0x36 = "ROL zp,X",
	0x38 = "SEC",
	0x39 = "AND Abs,Y",
	0x3D = "AND Abs,X",
	0x3E = "ROL Abs,X",
	0x40 = "RTI",
	0x41 = "EOR (zp,X)",
	0x45 = "EOR zp",
	0x46 = "LSR zp",
	0x48 = "PHA",
	0x49 = "EOR #",
	0x4A = "LSR",
	0x4C = "JMP Abs",
	0x4D = "EOR Abs",
	0x4E = "LSR Abs",
	0x50 = "BVC",
	0x51 = "EOR (zp),Y",
	0x55 = "EOR zp,X",
	0x56 = "LSR zp,X",
	0x58 = "CLI",
	0x59 = "EOR Abs,Y",
	0x5D = "EOR Abs,X",
	0x5E = "LSR Abs,X",
	0x60 = "RTS",
	0x61 = "ADC (zp,X)",
	0x65 = "ADC zp",
	0x66 = "ROR zp",
	0x68 = "PLA",
	0x69 = "ADC #",
	0x6A = "ROR",
	0x6C = "JMP (Abs)",
	0x6D = "ADC Abs",
	0x6E = "ROR Abs",
	0x70 = "BVS",
	0x71 = "ADC (zp),Y",
	0x75 = "ADC zp,X",
	0x76 = "ROR zp,X",
	0x78 = "SEI",
	0x79 = "ADC Abs,Y",
	0x7D = "ADC Abs,X",
	0x7E = "ROR Abs,X",
	0x81 = "STA (zp,X)",
	0x84 = "STY zp",
	0x85 = "STA zp",
	0x86 = "STX zp",
	0x88 = "DEY",
	0x8A = "TXA",
	0x8C = "STY Abs",
	0x8D = "STA Abs",
	0x8E = "STX Abs",
	0x90 = "BCC",
	0x91 = "STA (zp),Y",
	0x94 = "STY zp,X",
	0x95 = "STA zp,X",
	0x96 = "STX zp,Y",
	0x98 = "TYA",
	0x99 = "STA Abs,Y",
	0x9A = "TXS",
	0x9D = "STA Abs,X",
	0xA0 = "LDY #",
	0xA1 = "LDA (zp,X)",
	0xA2 = "LDX #",
	0xA4 = "LDY zp",
	0xA5 = "LDA zp",
	0xA6 = "LDX zp",
	0xA8 = "TAY",
	0xA9 = "LDA #",
	0xAA = "TAX",
	0xAC = "LDY Abs",
	0xAD = "LDA Abs",
	0xAE = "LDX Abs",
	0xB0 = "BCS",
	0xB1 = "LDA (zp),Y",
	0xB4 = "LDY zp,X",
	0xB5 = "LDA zp,X",
	0xB6 = "LDX zp,Y",
	0xB8 = "CLV",
	0xB9 = "LDA Abs,Y",
	0xBA = "TSX",
	0xBC = "LDY Abs,X",
	0xBD = "LDA Abs,X",
	0xBE = "LDX Abs,Y",
	0xC0 = "CPY #",
	0xC1 = "CMP (zp,X)",
	0xC4 = "CPY zp",
	0xC5 = "CMP zp",
	0xC6 = "DEC zp",
	0xC8 = "INY",
	0xC9 = "CMP #",
	0xCA = "DEX",
	0xCC = "CPY Abs",
	0xCD = "CMP Abs",
	0xCE = "DEC Abs",
	0xD0 = "BNE",
	0xD1 = "CMP (zp),Y",
	0xD5 = "CMP zp,X",
	0xD6 = "DEC zp,X",
	0xD8 = "CLD",
	0xD9 = "CMP Abs,Y",
	0xDD = "CMP Abs,X",
	0xDE = "DEC Abs,X",
	0xE0 = "CPX #",
	0xE1 = "SBC (zp,X)",
	0xE4 = "CPX zp",
	0xE5 = "SBC zp",
	0xE6 = "INC zp",
	0xE8 = "INX",
	0xE9 = "SBC #",
	0xEA = "NOP",
	0xEC = "CPX Abs",
	0xED = "SBC Abs",
	0xEE = "INC Abs",
	0xF0 = "BEQ",
	0xF1 = "SBC (zp),Y",
	0xF5 = "SBC zp,X",
	0xF6 = "INC zp,X",
	0xF8 = "SED",
	0xF9 = "SBC Abs,Y",
	0xFD = "SBC Abs,X",
	0xFE = "INC Abs,X"
};

RunTestProgram :: proc()
{
	using netlist_sim;

	memory := [65536]u8{};

	ParseProgram(strings.clone_to_cstring("./build/test.asm"), &memory[0]);

	fmt.println("Memory:");
	for i in 0..<20 do fmt.printf(" %.2x", memory[i]);
	fmt.println();
	fmt.println();

	state := SetupProcessor(memory[:]);
	defer FreeProcessorResources(state);

	fmt.println("+-------+------+----+----+-------------------+------+----+----+----+----+----------+");
	fmt.println("| cycle |  ab  | db | rw |       Fetch       |  pc  |  a |  x |  y |  s |     p    |");

	cycle := 0;
	for i in 0..<32
	{
		fmt.println("+-------+------+----+----+-------------------+------+----+----+----+----+----------+");

		fmt.print("|");
		cycle_string := fmt.tprint(cycle);
		fmt.print(strings.center_justify(cycle_string, max(8 - len(cycle_string), 0), " "));
		fmt.print("|");
		fmt.printf(" %04x ", ReadAB(state));
		fmt.print("|");
		fmt.printf(" %02x ", ReadDB(state));
		fmt.print("|");
		fmt.printf("  %d ", int(IsNodeHigh(state, rw)));
		fmt.print("|");
		instruction_string := (IsNodeHigh(state, sync) ? DisassemblyTable[ReadDB(state)] : "");
		fmt.print(strings.center_justify(instruction_string, max(20 - len(instruction_string), 0), " "));
		fmt.print("|");
		fmt.printf(" %04x ", ReadPC(state));
		fmt.print("|");
		fmt.printf(" %02x ", ReadA(state));
		fmt.print("|");
		fmt.printf(" %02x ", ReadX(state));
		fmt.print("|");
		fmt.printf(" %02x ", ReadY(state));
		fmt.print("|");
		fmt.printf(" %02x ", ReadS(state));
		fmt.print("|");
		pstring := ReadPString(state);
		fmt.print("", strings.center_justify(pstring, max(8 - len(pstring), 0), " "), "");
		fmt.print("|");
		fmt.println();
		
		Step(state);
		cycle += i % 2;
	}

	fmt.println("+-------+------+----+----+-------------------+------+----+----+----+----+----------+");
	fmt.println();

	fmt.println("Done");
}

INCOMING_LINE :: enum netlist_sim.Node_ID
{
	RESG,
	INTG,
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7,
	P0,
	P1,
	P2,
	P3,
	P4,
	P6,
	P7,
	// pos, nocr, sd1, sd2, cs, i/v
	RDY,
	SO,
}

IncomingLineNameMap := map[INCOMING_LINE]netlist_sim.Node_ID{
	.RESG = netlist_sim.NodeNameMap["RESG"],
	.INTG = netlist_sim.NodeNameMap["INTG"],
	.PD0  = netlist_sim.NodeNameMap["pd0"],
	.PD1  = netlist_sim.NodeNameMap["pd1"],
	.PD2  = netlist_sim.NodeNameMap["pd2"],
	.PD3  = netlist_sim.NodeNameMap["pd3"],
	.PD4  = netlist_sim.NodeNameMap["pd4"],
	.PD5  = netlist_sim.NodeNameMap["pd5"],
	.PD6  = netlist_sim.NodeNameMap["pd6"],
	.PD7  = netlist_sim.NodeNameMap["pd7"],
	.P0   = netlist_sim.NodeNameMap["p0"],
	.P1   = netlist_sim.NodeNameMap["p1"],
	.P2   = netlist_sim.NodeNameMap["p2"],
	.P3   = netlist_sim.NodeNameMap["p3"],
	.P4   = netlist_sim.NodeNameMap["p4"],
	.P6   = netlist_sim.NodeNameMap["p6"],
	.P7   = netlist_sim.NodeNameMap["p7"],
	.RDY  = netlist_sim.NodeNameMap["rdy"],
	.SO   = netlist_sim.NodeNameMap["so"],
};

OUTGOING_LINE :: enum netlist_sim.Node_ID
{
	DL_DB,
	DL_ADL,
	DL_ADH,
	Z_ADH0,
	Z_ADH17,
	ADH_ABH,
	ADL_ABL,
	PCL_PCL,
	ADL_PCL,
	I_PC,
	PCL_DB,
	PCL_ADL,
	PCH_PCH,
	ADH_PCH,
	PCH_DB,
	PCH_ADH,
	SB_ADH,
	SB_DB,
	Z_ADL0,
	Z_ADL1,
	Z_ADL2,
	S_ADL,
	SB_S,
	S_S,
	S_SB,
	NOTDB_ADD,
	DB_ADD,
	ADL_ADD,
	// 1/ADDC
	DAA,
	DSA,
	SUMS,
	ANDS,
	EORS,
	ORS,
	SRS,
	ADD_ADL,
	ADD_SB06,
	ADD_SB7,
	Z_ADD,
	SB_ADD,
	SB_AC,
	AC_DB,
	AC_SB,
	SB_X,
	X_SB,
	SB_Y,
	Y_SB,
	// P/DB
	// DB0/C
	// IR5/C
	// ACR/C
	// DB1/Z
	// DBZ/Z
	// DB2/I
	// IR5/I
	// DB3/D
	// IR5/D
	// DB6/V
	// AVR/V
	// I/V
	// DB7/N
}

// "ir5", "notir5"

OutgoingLineNameMap := map[OUTGOING_LINE]netlist_sim.Node_ID{
	.DL_DB     = netlist_sim.NodeNameMap["dpc43_DL/DB"],
	.DL_ADL    = netlist_sim.NodeNameMap["dpc41_DL/ADL"],
	.DL_ADH    = netlist_sim.NodeNameMap["dpc42_DL/ADH"],
	.Z_ADH0    = netlist_sim.NodeNameMap["dpc28_0ADH0"],
	.Z_ADH17   = netlist_sim.NodeNameMap["dpc29_0ADH17"],
	.ADH_ABH   = netlist_sim.NodeNameMap["dpc-2_ADH/ABH"],
	.ADL_ABL   = netlist_sim.NodeNameMap["dpc-1_ADL/ABL"],
	.PCL_PCL   = netlist_sim.NodeNameMap["dpc39_PCLPCL"],
	.ADL_PCL   = netlist_sim.NodeNameMap["dpc40_ADLPCL"],
	.I_PC      = netlist_sim.NodeNameMap["dpc36_#IPC"],
	.PCL_DB    = netlist_sim.NodeNameMap["dpc37_PCLDB"],
	.PCL_ADL   = netlist_sim.NodeNameMap["dpc38_PCLADL"],
	.PCH_PCH   = netlist_sim.NodeNameMap["dpc31_PCHPCH"],
	.ADH_PCH   = netlist_sim.NodeNameMap["dpc30_ADHPCH"],
	.PCH_DB    = netlist_sim.NodeNameMap["dpc33_PCHDB"],
	.PCH_ADH   = netlist_sim.NodeNameMap["dpc32_PCHADH"],
	.SB_ADH    = netlist_sim.NodeNameMap["dpc27_SBADH"],
	.SB_DB     = netlist_sim.NodeNameMap["dpc25_SBDB"],
	.Z_ADL0    = netlist_sim.NodeNameMap["0/ADL0"],
	.Z_ADL1    = netlist_sim.NodeNameMap["0/ADL1"],
	.Z_ADL2    = netlist_sim.NodeNameMap["0/ADL2"],
	.S_ADL     = netlist_sim.NodeNameMap["dpc5_SADL"],
	.SB_S      = netlist_sim.NodeNameMap["dpc6_SBS"],
	.S_S       = netlist_sim.NodeNameMap["dpc7_SS"],
	.S_SB      = netlist_sim.NodeNameMap["dpc4_SSB"],
	.NOTDB_ADD = netlist_sim.NodeNameMap["dpc8_nDBADD"],
	.DB_ADD    = netlist_sim.NodeNameMap["dpc9_DBADD"],
	.ADL_ADD   = netlist_sim.NodeNameMap["dpc10_ADLADD"],

	.DAA       = netlist_sim.NodeNameMap["dpc18_#DAA"],
	.DSA       = netlist_sim.NodeNameMap["dpc22_#DSA"],
	.SUMS      = netlist_sim.NodeNameMap["dpc17_SUMS"],
	.ANDS      = netlist_sim.NodeNameMap["dpc15_ANDS"],
	.EORS      = netlist_sim.NodeNameMap["dpc16_EORS"],
	.ORS       = netlist_sim.NodeNameMap["dpc13_ORS"],
	.SRS       = netlist_sim.NodeNameMap["dpc14_SRS"],
	.ADD_ADL   = netlist_sim.NodeNameMap["dpc21_ADDADL"],
	.ADD_SB06  = netlist_sim.NodeNameMap["dpc20_ADDSB06"],
	.ADD_SB7   = netlist_sim.NodeNameMap["dpc19_ADDSB7"],
	.Z_ADD     = netlist_sim.NodeNameMap["dpc12_0ADD"],
	.SB_ADD    = netlist_sim.NodeNameMap["dpc11_SBADD"],
	.SB_AC     = netlist_sim.NodeNameMap["dpc23_SBAC"],
	.AC_DB     = netlist_sim.NodeNameMap["dpc26_ACDB"],
	.AC_SB     = netlist_sim.NodeNameMap["dpc24_ACSB"],
	.SB_X      = netlist_sim.NodeNameMap["dpc3_SBX"],
	.X_SB      = netlist_sim.NodeNameMap["dpc2_XSB"],
	.SB_Y      = netlist_sim.NodeNameMap["dpc1_SBY"],
	.Y_SB      = netlist_sim.NodeNameMap["dpc0_YSB"],
};

main :: proc()
{
}
